
#include "CppUnitTest.h"
#include "ZoomSensCalc.h"
#include <format>
#include "ViewAngle.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace ZoomSensCalcTests
{






	TEST_CLASS(ZoomSensCalcTests)
	{
	public:


		/*
		Actual values directly from MCC:
			determined by setting view angle to exactly 0, then doing a single dot to the left.
			the resulting view angle is the expected increment for that sensitivity.
		*/
		TEST_METHOD(ViewAngleIncrementFinder_MatchesMCC_0dot1)
		{
			Assert::AreEqual(ViewAngle(0.00003878509233f), ViewAngle(viewAngleIncrementFinder(0.1f)));
		}

		TEST_METHOD(ViewAngleIncrementFinder_MatchesMCC_2dot1)
		{
			Assert::AreEqual(ViewAngle(0.0008144870517f), ViewAngle(viewAngleIncrementFinder(2.1f)));
		}

		TEST_METHOD(ViewAngleIncrementFinder_MatchesMCC_2dot7)
		{
			Assert::AreEqual(ViewAngle(0.001047197613f), ViewAngle(viewAngleIncrementFinder(2.7f)));
		}

		TEST_METHOD(ViewAngleIncrementFinder_MatchesMCC_3dot1)
		{
			Assert::AreEqual(ViewAngle(0.001202338142f), ViewAngle(viewAngleIncrementFinder(3.1f)));
		}

		TEST_METHOD(ViewAngleIncrementFinder_MatchesMCC_6dot8)
		{
			Assert::AreEqual(ViewAngle(0.002637386788f), ViewAngle(viewAngleIncrementFinder(6.8f)));
		}


		TEST_METHOD(ViewAngleIncrementFinder_MatchesMCC_10dot0)
		{
			Assert::AreEqual(ViewAngle(0.003878509626f), ViewAngle(viewAngleIncrementFinder(10.f)));
		}
		
		// from in-game test with these values
		TEST_METHOD(DotTowardAngle_Test)
		{
			auto result = dotTowardAngle(viewAngleIncrementFinder(6.8f), 3.0f, 3.1f);
			Assert::AreEqual(ViewAngle(3.097583294f), ViewAngle(result[0]));
			Assert::AreEqual(ViewAngle(3.10022068f), ViewAngle(result[1]));
		}

		// from in-game test with these values
		TEST_METHOD(AngleAfterTurns_Test_Right)
		{
			Assert::AreEqual(ViewAngle(6.282964706f), ViewAngle(angleAfterTurns(viewAngleIncrementFinder(6.8f), 0.1f, 1))); 
		}

		// from in-game test with these values
		TEST_METHOD(AngleAfterTurns_Test_Left)
		{
			Assert::AreEqual(ViewAngle(0.001431465149f), ViewAngle(angleAfterTurns(viewAngleIncrementFinder(6.8f), 6.1f, -1)));
		}
	};
}
