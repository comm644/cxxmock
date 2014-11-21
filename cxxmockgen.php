#!/usr/bin/env php
<?php

class CxxMock
{

	function __construct()
	{
		print "#include <cxxmock/cxxmock.h>\n";
	}

	function getArgList($m)
	{
		$n = 6;
		$args = array();
		for ($n = 9; $n < count($m[0]); $n+=5) {
			$args[] = $m[0][$n];
		}
		return implode(',', $args);
	}

	function generateMock($file)
	{
		$type = "\s*((const\s+)?[\w:]+\s*[&*]?)\s+";
		$name = "(\w+)";
		$arg = "({$type}{$name})";
		$arglist = "{$arg}?([,]?{$arg}?)*";
		$methodRx = "/(virtual\s+({$type}{$name})\($arglist?\s*\))\s*=\s*0;/";

		$rxClassLine = '/class\s+(\w+)\s*{?/';

		$namespaceRx = '/namespace\s+(\w+)\s*({)?/';

		$inclass = false;
		//print "//$methodRx\n";

		$namespaces = array();

		$rxNamespace = "(namespace\s+(\w+)\s*{)";
		$rxClass = "(class\s+(\w+)\s*[:]?.*?{)";
		$rxClose = "({|})";
		$rx = "/$rxNamespace+|$rxClass+|$rxClose/";

		preg_match_all($rx, file_get_contents($file), $m, PREG_SET_ORDER);
		$programm = array();
		foreach ($m as $match) {
			$programm[] = str_replace("\n", ' ', $match[0]);
		}

		print "#include \"$file\"\n\n";

		$expected = reset($programm);
		list( $keyword ) = explode(" ", $expected);
		foreach (explode("\n", file_get_contents($file)) as $line) {
			if ($keyword == "{") {
				list( $keyword ) = explode(" ", next($programm));
				list( $keyword ) = explode(" ", next($programm));
			}
			while ($keyword == "namespace") {
				$namespaces[] = current($programm) . "\n";
				list( $keyword ) = explode(" ", next($programm));
			}

			if ($keyword == "class") {
				$rc = preg_match_all($rxClassLine, $line, $m, PREG_SET_ORDER);
				if (!$rc) {
					continue;
				}
				if ( strpos( $line, ';' ) ) {
					continue; //forward decl
				}
	
				$inclass = true;
				$classHead = '';
				print implode('', $namespaces);

				$class = $m[0][1];
				$classHead .= "class CXXMOCK_DECL( {$class} )\n";
				$classHead .= "{\n";

				list( $keyword ) = explode(" ", next($programm));
				continue;
			}

			if ($inclass && $keyword == "}") {
				if ($inclass && preg_match("/};/", $line)) {
					if (!$classHead) {
						print "};\n";
						print "CXXMOCK_IMPL($class);\n\n";
						print str_repeat("}", count($namespaces)) . "\n\n";
					}

					$inclass = false;
					list( $keyword ) = explode(" ", next($programm));
					continue;
				}

				$rc = preg_match_all($methodRx, $line, $m, PREG_SET_ORDER);

				if (!$rc) {
					continue;
				}
				//print_r( $m);
				print $classHead;
				$classHead = '';
				
				$retvalue = trim($m[0][3]);
				
				$return = ( "void" == $retvalue ) ? "" : "return ";
				
				if ($retvalue == "void") {
					$retvalue = "int";
				}
				
				

				print "\t{$m[0][1]}\n";
				print "\t{\n";
				if (count($m[0]) == 6) {
					print "\t\t{$return}CXXMOCK_GET( {$retvalue} );\n";
				}
				else if ($m[0][3] == "void") {
					$args = $this->getArgList($m);
					print "\t\t{$return}CXXMOCK_SET( {$args} );\n";
				}
				else {
					$args = $this->getArgList($m);

					print "\t\t{$return}CXXMOCK( {$retvalue}, {$args} );\n";
				}
				print "\t}\n";
				continue;
			}
			if ($keyword == '}') {
				array_pop($namespaces);
				list( $keyword ) = explode(" ", next($programm));
				continue;
			}
		}
	}

}

$argc = $_SERVER["argc"];

if ($argc == 1) {
	print "Usage: {$_SERVER['argv'][0]} <header> [<header>],,,\n";
	exit;
}

$cxxmock = new CxxMock();
for ($i = 1; $i < $argc; $i++) {
	$cxxmock->generateMock($_SERVER["argv"][$i]);
}

