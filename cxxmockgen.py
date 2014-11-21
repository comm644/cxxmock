#!/usr/bin/python
'''Usage: %s [OPTIONS] <input file(s)>
Generate mock objects implementation for CxxMock subsystem.

  -v, --version          Write CxxMock version
  -o, --output=NAME      Write output to file NAME
'''

version = "1.0.10"

import re
import sys
import getopt
import glob
import string
import pprint
import random

# Global variables
suites = []
suite = None
inBlock = 0

outputFileName = None
headers = []

rxTypeBase = "\s*(?:const\s+)?(?:unsigned\s+)?[\w:]+\s*";
rxType = "(" + rxTypeBase + "(?:<\s*(?:template|class)?" + rxTypeBase + ">)?[&*]?)\s+";

rxName = "(\w+)\s*";
rxArg = "(" + rxType + "&?" + rxName + ")";
rxArgList = "([,]?" + rxArg +")*";
rxMethod = re.compile("(virtual\s+("+rxType+ rxName +")\((.*)\)(\s*const)?)\s*=\s*0;");
rxClassLine = 'class\s+(\w+)\s*{?';
rxNamespace = '/namespace\s+(\w+)\s*({)?/';
rxNamespaceLine = "(namespace\s+(\w+)\s*{)";
rxForwardDecl = "\s*(class\s+(\w+)\s*;)";
rxClass = "(class\s+(\w+)\s*[^{]*{)";
rxClose = '({|})';
rxBlocks = "" + rxNamespaceLine + "+|" + rxForwardDecl + "+|" + rxClass + "+|" + rxClose + "";
output = sys.stderr

pp = pprint.PrettyPrinter(indent=4)

def main():
    '''The main program'''
    files = parseCommandline()
    scanInputFiles( files )
    #writeOutput()

def usage( problem = None ):
    '''Print usage info and exit'''
    if problem is None:
        print usageString()
        sys.exit(0)
    else:
        sys.stderr.write( usageString() )
        abort( problem )

def usageString():
    '''Construct program usage string'''
    return __doc__ % sys.argv[0]

def abort( problem ):
    '''Print error message and exit'''
    sys.stderr.write( '\n' )
    sys.stderr.write( problem )
    sys.stderr.write( '\n\n' )
    sys.exit(2)

def parseCommandline():
    '''Analyze command line arguments'''
    try:
        options, patterns = getopt.getopt( sys.argv[1:], 'o:v',
                                           ['version', 'output=' ] )
    except getopt.error, problem:
        usage( problem )
        
    setOptions( options )
    
    return setFiles( patterns )

def setOptions( options ):
    '''Set options specified on command line'''
    global outputFileName 
    for o, a in options:
        if o in ('-v', '--version'):
            printVersion()
        elif o in ('-o', '--output'):
            outputFileName = a

def printVersion():
    '''Print CxxMock version and exit'''
    global version
    sys.stdout.write( "This is CxxMock version %s.\n" % version )
    sys.exit(0)

def setFiles( patterns ):
    '''Set input files specified on command line'''
    files = expandWildcards( patterns )
    if len(files) is 0 :
        usage( "No input files found" )
    return files

def expandWildcards( patterns ):
    '''Expand all wildcards in an array (glob)'''
    fileNames = []
    for pathName in patterns:
        patternFiles = glob.glob( pathName )
        for fileName in patternFiles:
            fileNames.append( fixBackslashes( fileName ) )
    return fileNames

def fixBackslashes( fileName ):
    '''Convert backslashes to slashes in file name'''
    return re.sub( r'\\', '/', fileName, 0 )


def scanInputFiles(files):
    '''Scan all input files for test suites'''
    global output
    output = startOutputFile()
    defineName = "__mocks_%s__generated" % ( int(random.random() * 100000))
    output.write( "#ifndef %s\n" % defineName )
    output.write( "#define %s\n"% defineName)
    
    for file in files:
        scanInputFile(file)

    output.write( "#endif //%s\n" % defineName)


def scanInputFile(fileName):
    '''Scan single input file for interfaces'''
    
   # print("\n\n//process " + fileName )
    
    content = open(fileName).read()

    programm = getProgramm(content)

    output.write( "#include \"" + fileName + "\"\n\n")

    programmPos = 0
    expected = programm[programmPos]  
    keyword =  expected.split(" ")[0]
    namespaces = []
    inclass = 0
    
    for line in content.split("\n"):

        if keyword == "{":
            programmPos += 1
            keyword = programm[programmPos].split(" ")[0]
            
            programmPos += 1
            keyword = programm[programmPos].split(" ")[0]

        while keyword == "namespace":
            namespaces.append( programm[++programmPos] )
            programmPos += 1
            keyword = programm[programmPos].split(" ")[0]
        
        if keyword == "class":
            if len( re.findall( rxForwardDecl, line ) ) != 0 :
                # pp.pprint( "forward decl" );
                programmPos += 1
                keyword = programm[programmPos].split(" ")[0]
                
            else:
                matches = re.findall(rxClassLine, line)

                if len(matches) == 0:
                    continue
                
                if line.find(';') != -1:
                    #forward decl
                    continue;

                inclass = 1
                classHead = ''
                output.write(  ' '.join( namespaces ) )
                
                className = matches[0]
                classHead += "class CXXMOCK_DECL( %s )\n" % className
                classHead += "{\n"

                programmPos += 1
                keyword = programm[programmPos].split(" ")[0]
                continue
        
        #print '//kw1:%s  -' % inclass  + keyword  + '-  line:' + line   
        if keyword == '}':
            if inclass == 0 :
                if len( namespaces ) > 0 :
                    # pp.pprint( "pop NS" );    
                    namespaces.pop()
                
                if programmPos +1 < len( programm ) :
                    programmPos += 1
                    keyword = programm[programmPos].split(" ")[0]

                continue
            
            
            if inclass == 1 and len(re.findall( "};", line)) > 0:
                if classHead == '':
                    output.write( "};\n")
                    output.write( "CXXMOCK_IMPL(%s);\n\n" % className)
                    output.write( "}" * len(namespaces) + "\n\n")

                inclass = 0
                programmPos += 1

                if  programmPos >= len( programm ):
                    continue
					
                keyword = programm[programmPos].split(" ")[0]
                continue

            matches = rxMethod.findall(line)
            # pp.pprint(matches)
			
            if len(matches) == 0 :
                continue;
            
            matches = matches[0]
            output.write( classHead )
            classHead = ''

            retvalue = matches[2].strip()

            if  "void" == retvalue: 
                 returnStr = ''
            else:
                 returnStr = "return "

            if retvalue == "void" :
                retvalue = "int"


            output.write( "\t%s\n" % matches[0])
            output.write( "\t{\n")



            if retvalue.find("&") != -1:
                retvalue = retvalue.replace("&", "").replace("const", "") 
                output.write("\t\tstatic " + retvalue + " __cxxmock_retvalue;\n")
                returnStr = "return __cxxmock_retvalue = "
            
            argMatches =  re.compile(rxArg).findall( matches[4].strip() );

            if len(argMatches) == 0 :
                output.write( "\t\t%sCXXMOCK_GET( %s );\n" % ( returnStr, retvalue ))
                
            elif matches[2] == "void":
                args = getArgList(argMatches);
                output.write( "\t\t%sCXXMOCK_SET( %s );\n" % (returnStr, args))
            else:
                args = getArgList(argMatches)
                output.write( "\t\t%sCXXMOCK( %s, %s );\n" % ( returnStr, retvalue, args ))

            output.write( "\t}\n");
            continue
        
        
    return


def getArgList(matches):
    args = []

    # pp.pprint( matches )
    for n in matches:
        if n[0].strip() != '' :
            args.append( n[2] )
        
#    pp.pprint( args  )
    return ', '.join( args );



def getProgramm(content):
    # Remove all inline comments
    content = re.sub(r'//.*\n', '', content)

    # Get programm structure
    matches = re.findall(rxBlocks, content)
    pp = pprint.PrettyPrinter(indent=4)
    
    programm = []
    for match in matches:
        for keyword in match:
            if keyword == '' : continue;
            if keyword == '{' : programm.append( keyword ); continue;
            if keyword == '}' : programm.append( keyword ); continue;
            if keyword.split(" ")[0] == "namespace":
                programm.append( keyword )
                
            if keyword.split(" ")[0] == "class":
                programm.append( keyword )
            
    # pp.pprint( programm)
    return programm


def scanInputLine( fileName, lineNo, line ):
    '''Scan single input line for interesting stuff'''
    scanLineForExceptionHandling( line )
    scanLineForStandardLibrary( line )

    scanLineForSuiteStart( fileName, lineNo, line )

    global suite
    if suite:
        scanLineInsideSuite( suite, lineNo, line )


def writeOutput():
    '''Create output file'''
    writeSimpleOutput()

def writeSimpleOutput():
    '''Create output not based on template'''
    output = startOutputFile()
    writePreamble( output )
    writeMain( output )
    writeWorld( output )
    output.close()


def startOutputFile():
    '''Create output file and write header'''
    if outputFileName is not None:
        output = open( outputFileName, 'w' )
    else:
        output = sys.stdout
    output.write( "/* Generated file, do not edit. Do not commit under VCS. */\n\n" )
    output.write( "#include <cxxmock/cxxmock.h>\n\n" )
    return output


main()
