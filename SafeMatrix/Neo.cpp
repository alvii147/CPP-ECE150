////////////////////////////////////////////////////////////////////////////////
//
// Neo.cpp
// Test Driver for SafeMatrix class
// Inputs:  none
// Outputs: Results of testing SafeMatrix Class, displayed to cout
// Operation: test all methods of SafeMatrix class
//
// Change History
// 26 November 2018; PASW; Initial version: only implements
//                                          (1) basic test setup
//                                          (2) testing of ...
//                                          (3) display of results
//

#include <iostream>
#include <cmath>
#include "SafeMatrix.h"
#include "TestCase.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////
//
// Testcases for appendRow()
// Uses class TestCase
//


class TestAppendRow : public TestCase {
public:
  bool testBasicAppend();
  bool testMismatchAppend();
  bool testNaMAppend();

  bool run();
  int  setup() { return 0; } ;

#define NUM_COLS 3
  TestAppendRow() : data1(0,NUM_COLS), data2(-1,0) {};
private:
  SafeMatrix data1;
  SafeMatrix data2;             // Should be NaM
};

bool TestAppendRow::run() {
  setup();
  if (!testBasicAppend() ||
      !testMismatchAppend() ||
      !testNaMAppend()) 
    return false;
  return true;
}

bool TestAppendRow::testBasicAppend() {
  float data[] = { 1.1, 2.2, 3.3 };
  bool retVal = false;
  const char desc[] = "Append Row: Basic Append";
  if (!data1.appendRow(NUM_COLS, data) ||
      (data1(0,0) != data[0]) ||
      (data1(0,1) != data[1]) ||
      (data1(0,2) != data[2]))
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

bool TestAppendRow::testMismatchAppend() {
  float data[] = { 1.1, 2.2, 3.3 };
  bool retVal = true;
  const char desc[] = "Append Row: Mismatch Append";
  if (data1.appendRow(NUM_COLS-1, data))
    retVal = false;
  if (((data1.dimensions()).rows != 1) || 
      ((data1.dimensions()).cols != NUM_COLS)) 
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

bool TestAppendRow::testNaMAppend() {
  float data[] = { 1.1, 2.2, 3.3 };
  bool retVal = true;
  const char desc[] = "Append Row: NaM Append";
  if (data2.appendRow(0, data))
    retVal = false;
  if (!data2.isNaM())
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

////////////////////////////////////////////////////////////////////////////////
//
// Testcases for operator()
// Uses class TestCase
//


class TestParens : public TestCase
{
	public:
	int testRHSValid();
	int testLHSValid();
	int testRHSInvalid();
	int testLHSInvalid();
	
	bool run();
	int setup()
	{
		return false;
	}
};

bool TestParens::run()
{
	setup();
	if(!testRHSValid() || !testLHSValid() || !testRHSInvalid() || !testLHSInvalid())
	{
		return false;
	}
	return true;
}

int TestParens::testRHSValid()
{
	int test = 0;
	const char desc[] = "TestParens: testRHSValid";
	float data1[4] = {2, -5, -3, 5};
	float data2[4] = {8, 6, 3, 0};
	float data3[4] = {-5, -6, -4, -2};
	SafeMatrix m(4, data1);
	m.appendColumn(4, data2);
	m.appendColumn(4, data3);
	int x = m(0, 1);
	if(x == 8)
	{
		test = 1;
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

int TestParens::testLHSValid()
{
	int test = 0;
	const char desc[] = "TestParens: testLHSValid";
	float data1[4] = {0, 0, -3, -9};
	float data2[4] = {8, 0, 3, 0};
	float data3[4] = {3, 7, -4, -2};
	SafeMatrix m(4, data1);
	m.appendColumn(4, data2);
	m.appendColumn(4, data3);
	int x = m(3, 0);
	if(x == -9)
	{
		test = 1;
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

int TestParens::testRHSInvalid()
{
	int test = 0;
	const char desc[] = "TestParens: testRHSInvalid";
	float data1[4] = {2, -5, -3, 5};
	float data2[4] = {8, 6, 3, 0};
	float data3[4] = {-5, -6, -4, -2};
	SafeMatrix m(4, data1);
	m.appendColumn(4, data2);
	m.appendColumn(4, data3);
	int x = m(0, -2);
	if(x < -2147483647 || x > 2147483647 || x != x)
	{
		test = 1;
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

int TestParens::testLHSInvalid()
{
	int test = 0;
	const char desc[] = "TestParens: testLHSInvalid";
	float data1[4] = {2, -5, -3, 5};
	float data2[4] = {8, 6, 3, 0};
	float data3[4] = {-5, -6, -4, -2};
	SafeMatrix m(4, data1);
	m.appendColumn(4, data2);
	m.appendColumn(4, data3);
	int x = m(-6, 0);
	if(x < -2147483647 || x > 2147483647 || x != x)
	{
		test = 1;
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

////////////////////////////////////////////////////////////////////////////////
//
//

class TestIdentity : public TestCase
{
	public:
	bool testBasicIdentity();
	bool testerrIdentity();
	
	bool run();
	int setup()
	{
		return false;
	}
};

bool TestIdentity::run()
{
	setup();
	if(!testBasicIdentity() || !testerrIdentity())
	{
		return false;
	}
	return true;
}

bool TestIdentity::testBasicIdentity()
{
	int test = 1;
	const char desc[] = "TestIdentity: testBasicIdentity";
	SafeMatrix m = SafeMatrix::identity(4);
	Dimensions d = m.dimensions();
	int r = d.rows;
	int c = d.cols;
	if(r != 4 || c != 4)
	{
		test = 0;
	}
	for(int i = 0; i<(r*c); i++)
	{
		if(i/c == i%c)
		{
			if(m(i/c, i%c) != 1)
			{
				test = 0;
			}
		}
		else
		{
			if(m(i/c, i%c) != 0)
			{
				test = 0;
			}
		}
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

bool TestIdentity::testerrIdentity()
{
	int test = 1;
	const char desc[] = "TestIdentity: testerrIdentity";
	SafeMatrix m = SafeMatrix::identity(-5);
	Dimensions d = m.dimensions();
	int r = d.rows;
	int c = d.cols;
	if(r != NOT_A_MATRIX || c != NOT_A_MATRIX)
	{
		test = 0;
	}
	if(!m.isNaM())
	{
		test = 0;
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

////////////////////////////////////////////////////////////////////////////////
//
//

class TestDimensions : public TestCase
{
	public:
	bool testBasicDimensions();
	
	bool run();
	int setup()
	{
		return false;
	}
};

bool TestDimensions::run()
{
	setup();
	if(!testBasicDimensions())
	{
		return false;
	}
	return true;
}

bool TestDimensions::testBasicDimensions()
{
	int test = 1;
	const char desc[] = "TestDimensions: testBasicDimensions";
	SafeMatrix m(34, 97);
	Dimensions d = m.dimensions();
	int r = d.rows;
	int c = d.cols;
	if(r != 34 || c != 97)
	{
		test = 0;
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

////////////////////////////////////////////////////////////////////////////////
//
//

class TestOperAdd : public TestCase
{
	public:
	bool testBasicAdd();
	
	bool run();
	int setup()
	{
		return false;
	}
};

bool TestOperAdd::run()
{
	setup();
	if(!testBasicAdd())
	{
		return false;
	}
	return true;
}

bool TestOperAdd::testBasicAdd()
{
	int test = 0;
	const char desc[] = "TestOperAdd: testBasicAdd";
	float data1[2] = {2, 4};
	float data2[2] = {8, -9};
	float data3[2] = {4, 0};
	float data4[2] = {0, -1};
	SafeMatrix m(2, data1);
	m.appendColumn(2, data2);
	SafeMatrix n(2, data3);
	n.appendColumn(2, data4);
	SafeMatrix a = m+n;
	if(a(0, 0) == 6 && a(0, 1) == 8 && a(1, 0) == 4 && a(1, 1) == -10)
	{
		test = 1;
	}
	_perTestCaseResults[_testcaseNumber] = test;
	output(desc);
	cleanup();
	return test;
}

int main() {

  TestCase t0;
  t0.run();

  TestAppendRow t1;
  t1.run();

  TestParens t2;
  t2.run();
  
  TestIdentity t3;
  t3.run();
  
  TestDimensions t4;
  t4.run();
  
  TestOperAdd t5;
  t5.run();

  t0.terminate();
  
  return 0;
}
