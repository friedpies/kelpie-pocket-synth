/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Test_h
#define Test_h

// include types & constants of Wiring core API
#include "WConstants.h"

// library interface description
class Test
{
  // user-accessible "public" interface
  public:
    Test(int);
    void doSomething(void);

  // library-accessible "private" interface
  private:
    int value;
    void doSomethingSecret(void);
};

#endif

