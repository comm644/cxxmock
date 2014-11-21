Set return value
-----------------------
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TS_EXPECT_CALL( object->method() )
          .returns( retvalue );
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Disable repeating constraint.
-----------------------
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TS_EXPECT_CALL( object->method() )
         .repeat().any();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Set repeating constraint to once time..
-----------------------
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TS_EXPECT_CALL( object->method() )
         .repeat().once();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Set repeating constraint to specified times..
-----------------------
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TS_EXPECT_CALL( object->method() )
         .repeat().times(5);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Disable argument constraint:
-----------------------
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TS_EXPECT_CALL( object->method() )
        .ignoreArguments();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Return same value any time for any arguments.
-----------------------

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TS_EXPECT_CALL( object->method("value1", 5) )
        .ignoreArguments()
        .returns( 10 )
        .repeat().any();

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
