
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
			Assert::AreEqual(ViewAngle(3.097583294f), ViewAngle(result.closestRightDot));
			Assert::AreEqual(ViewAngle(3.10022068f), ViewAngle(result.closestLeftDot));
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

	

		void ZoomSensManipCalc_MatchesSpreadsheet(float viewAngleIncrement, float startingAngle, float targetAngle, int zoomDots, float spreadsheetZoomSensitivityManip, float zoomFactor, int counterClockwiseTurns) const noexcept
		{
			auto zoomSensResult = calcZoomSensManip(viewAngleIncrement, startingAngle, targetAngle, targetAngle, 2, counterClockwiseTurns, 0, 5);

			bool foundMatch = false;
			for (auto& manip : zoomSensResult)
			{
				if (manip.DotsToFirstAngle == zoomDots) // the particular test case we care about
				{
					// these aren't really view angles but they wouldn't go outside that range anyway- this lets the assert message show us all the digits of the float. 
					// NOTE: the spreadsheet math is not PERFECTLY accurate, unlike what this cpp math ought to be.
					// So we'll call this test a pass if the result is within 0.001% of the spreadsheet.

					float differenceToSpreadsheet = std::abs(manip.ZoomSensitivityValue - spreadsheetZoomSensitivityManip);
					Assert::IsTrue(differenceToSpreadsheet < (spreadsheetZoomSensitivityManip / 100000.f), StringToWString(std::format("Too different from spreadsheet. Expected: <{}> Actual:<{}>",  ExactFloatToString(spreadsheetZoomSensitivityManip), ExactFloatToString(manip.ZoomSensitivityValue))).c_str());
					return;
				}
			}
			Assert::Fail(L"A zoom sensitivity manip wasn't found for this test case");
		}

		// testing against results in original "Sens Manip Calculator Sheet" here https://docs.google.com/spreadsheets/d/1BZcVoXNZBW0ofkO2KnobSMMcIDaW_DQyEmuHRdNN7EU/edit?gid=55880604#gid=55880604

		TEST_METHOD(ZoomSensManip_SCBeachSkip_1DotLeft_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, 1, 0.11896586f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_2DotLeft_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, 2, 0.05948293f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_3DotLeft_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, 3, 0.03965529f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_4DotLeft_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, 4, 0.02974147f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_5DotLeft_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, 5, 0.02379317f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_1DotRight_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, -1, 1.88103396f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_2DotRight_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, -2, 0.94051698f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_3DotRight_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, -3, 0.62701132f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_4DotRight_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, -4, 0.47025849f, 2, 0);
		}

		TEST_METHOD(ZoomSensManip_SCBeachSkip_5DotRight_MatchesSpreadsheet)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, -5, 0.37620679f, 2, 0);
		}



		// does a calculated zoom sensitivity manip ACTUALLY achieve the target angle, beginning at startingAngle?
		void DoesCalculatedZoomSensManipActuallyWork(float viewAngleIncrement, float startingAngle, float targetAngle, float zoomFactor, int counterClockwiseTurns)
		{
			auto zoomSensResult = calcZoomSensManip(viewAngleIncrement, startingAngle, targetAngle, targetAngle, 2, counterClockwiseTurns, 0, 5);
			Assert::IsTrue(zoomSensResult.size() == 10, StringToWString(std::format("Not enough results! {} manips calculated", zoomSensResult.size())).c_str());
			
			
			// test each result
			for (auto& manip : zoomSensResult)
			{
	/*			if (manip.ZoomSensitivityValue < 0.1f || manip.ZoomSensitivityValue > 2.f)
					continue;*/

				// Do the zoom sens manip
				float closestIncrementHigh = startingAngle + (manip.DotsToFirstAngle * manip.ZoomSensitivityValue * viewAngleIncrement / zoomFactor);
				float closestIncrementLow = closestIncrementHigh;

				// move at regular view angle increment toward target angle
				while (closestIncrementHigh < targetAngle) // this var will end up either equal to or slightly greater than (leftwards) target angle low
					closestIncrementHigh += viewAngleIncrement;

				while (closestIncrementLow > targetAngle) // this var will end up either equal to or slightly less than (rightwards) target angle high
					closestIncrementLow -= viewAngleIncrement;

				// if manip worked, startingAngle should exactly equal targetAngle
				Assert::IsTrue(closestIncrementHigh >= targetAngle && closestIncrementLow <= targetAngle,
				StringToWString(std::format("Zoom sens val {} with {} dots failed, TargetAngle: <{}> ClosestLow: <{}> ClosestRight: <{}>", manip.ZoomSensitivityValue, manip.DotsToFirstAngle, targetAngle, closestIncrementLow, closestIncrementHigh)).c_str());
			}

		

		}


		TEST_METHOD(ZoomSensManip_SCBeachSkip_ActuallyWorks)
		{
			DoesCalculatedZoomSensManipActuallyWork(viewAngleIncrementFinder(6.8f), SC_startingAngle, SC_targetAngle, 2, -1); // exact manip
		}


		TEST_METHOD(ZoomSensManip_343_RS3_MatchesSpreadsheet_1DotRight)
		{
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), 5.3184395f, 3.4001875f, -1, 1.95533666f, 2, 1);
		}

		TEST_METHOD(ZoomSensManip_343_RS3_ActuallyWorks)
		{
			DoesCalculatedZoomSensManipActuallyWork(viewAngleIncrementFinder(6.8f), 5.3184395f, 3.4001875f, 2, -1);
		}


		TEST_METHOD(ZoomSensManip_DOUBLE)
		{
			// gonna do a RS3 subpixel + the CJSS subpixel
			float viewAngleIncrement = viewAngleIncrementFinder(6.8f);
			float startingAngle = 5.3184395f;
			float RS3Target = 3.4001875f;
			float CJSSTarget = 5.0436749f;
			float zoomFactor = 2;
			int counterClockwiseTurns = -1;
			int maxDots = 10000; // SURELY it'll find something with 10000 dots?

			auto zoomSensResult = calcZoomSensManip(viewAngleIncrementFinder(6.8f), startingAngle, RS3Target, CJSSTarget, zoomFactor, counterClockwiseTurns, 0, maxDots);
			Assert::IsFalse(zoomSensResult.empty(), L"Not enough results! No manips calculated");


			// test each result
			for (auto& manip : zoomSensResult)
			{
				/*			if (manip.ZoomSensitivityValue < 0.1f || manip.ZoomSensitivityValue > 2.f)
								continue;*/

								// Do the zoom sens manip
				float RS3AttemptAngle = startingAngle + (manip.DotsToFirstAngle * manip.ZoomSensitivityValue * viewAngleIncrement / zoomFactor);

				// move at regular view angle increment toward RS3Target
				while (RS3AttemptAngle < RS3Target) // this var will end up either equal to or slightly greater than (leftwards) target angle 
					RS3AttemptAngle += viewAngleIncrement;

				float debugRS3High = RS3AttemptAngle;

				while (RS3AttemptAngle > RS3Target) // this var will end up either equal to or slightly less than (rightwards) target angle
					RS3AttemptAngle -= viewAngleIncrement;

				// if manip worked, RS3AttemptAngle should exactly equal targetAngle
				Assert::IsTrue(RS3AttemptAngle == RS3Target,
					StringToWString(std::format("Zoom sens val {} with {} dots failed to RS3, TargetAngle: <{}> RS3AttemptAngleLow: <{}> RS3AttemptAngleHigh <{}>", manip.ZoomSensitivityValue, manip.DotsToFirstAngle, RS3Target, RS3AttemptAngle, debugRS3High)).c_str());



				// do it AGAIN but start from RS3AttemptAngle, use extra dots, attempt to get to CJSS
				// Do the zoom sens manip
				float CJSSAttemptAngle = RS3AttemptAngle + (manip.SecondAngleExtraDots * manip.ZoomSensitivityValue * viewAngleIncrement / zoomFactor);

				// move at regular view angle increment toward RS3Target
				while (CJSSAttemptAngle < CJSSTarget) // this var will end up either equal to or slightly greater than (leftwards) target angle
					CJSSAttemptAngle += viewAngleIncrement;

				float debugCJSSHigh = CJSSAttemptAngle;

				while (CJSSAttemptAngle > CJSSTarget) // this var will end up either equal to or slightly less than (rightwards) target angle
					CJSSAttemptAngle -= viewAngleIncrement;

				// if manip worked, CJSSAttemptAngle should exactly equal targetAngle
				Assert::IsTrue(CJSSAttemptAngle == CJSSTarget,
					StringToWString(std::format("Zoom sens val {} with {} dots failed to CJSS, TargetAngle: <{}> CJSSAttemptAngleLow: <{}> CJSSAttemptAngleHigh <{}>", manip.ZoomSensitivityValue, manip.SecondAngleExtraDots, CJSSTarget, CJSSAttemptAngle, debugCJSSHigh)).c_str());



			}

		}


		TEST_METHOD(TwoTrickSameManipTest_1_NoTurns)
		{
			float startingAngle = 5.8857827f; // library start
			float zoomSensThatWorks = 1.5f; // will check against
			// then do one dot right
			float targetAngle1 = 5.1400619f; // and you can reach this angle
				// then do 2 dots left
			float targetAngle2 = 3.8543358f; // and you can reach this angle

			float viewAngleIncrement = viewAngleIncrementFinder(6.8f);

			auto zoomSensResult = calcZoomSensManip(viewAngleIncrementFinder(6.8f), startingAngle, targetAngle1, targetAngle2, 2, 0, 0, 5);
			Assert::IsFalse(zoomSensResult.empty(), L"Not enough results! No manips calculated");


			std::stringstream ss;
			for (auto& manip : zoomSensResult)
			{
				ss << manip << std::endl;
				if (manip.DotsToFirstAngle == -1 && manip.SecondAngleExtraDots == 2)
				{
					if (manip.ZoomSensitivityValue == zoomSensThatWorks)
						return; // Test passed!

					// calculated zs may be different from what we used but still actually have the same result!
					// so test for being within 1%
					float differenceFromUsedValue = std::abs(zoomSensThatWorks - manip.ZoomSensitivityValue);
					if (differenceFromUsedValue / zoomSensThatWorks < 0.01)
						return; // Test passed!
					else
						Assert::Fail((StringToWString(std::format("Manip found with correct dots but incorrect sensitivity value. Expected: <{}> Actual: <{}>", zoomSensThatWorks, manip.ZoomSensitivityValue))).c_str());
				}
			}




			Assert::Fail(StringToWString(std::format("Reproduction manip not found! But we did find: \n{}", ss.str())).c_str());
		}


		TEST_METHOD(TwoTrickSameManipTest_2_TurnBeforeFirst)
		{
			float startingAngle = 5.8857827f; // library start
			float zoomSensThatWorks = 1.5f; // will check against
			// then do one dot right & 1 counter clockwise turn
			float targetAngle1 = 3.7386785f; // and you can reach this angle
			// then do 2 dots left
			float targetAngle2 = 5.3778143f; // and you can reach this angle

			float viewAngleIncrement = viewAngleIncrementFinder(6.8f);

			auto zoomSensResult = calcZoomSensManip(viewAngleIncrementFinder(6.8f), startingAngle, targetAngle1, targetAngle2, 2, 1, 1, 5);
			Assert::IsFalse(zoomSensResult.empty(), L"Not enough results! No manips calculated");


			std::stringstream ss;
			for (auto& manip : zoomSensResult)
			{
				ss << manip << std::endl;
				if (manip.DotsToFirstAngle == -1 && manip.SecondAngleExtraDots == 2)
				{
					if (manip.ZoomSensitivityValue == zoomSensThatWorks)
						return; // Test passed!

					// calculated zs may be different from what we used but still actually have the same result!
					// so test for being within 1%
					float differenceFromUsedValue = std::abs(zoomSensThatWorks - manip.ZoomSensitivityValue);
					if (differenceFromUsedValue / zoomSensThatWorks < 0.01)
						return; // Test passed!
					else
						Assert::Fail((StringToWString(std::format("Manip found with correct dots but incorrect sensitivity value. Expected: <{}> Actual: <{}>", zoomSensThatWorks, manip.ZoomSensitivityValue))).c_str());
				}
			}




			Assert::Fail(StringToWString(std::format("Reproduction manip not found! But we did find: \n{}", ss.str())).c_str());
		}
	

		TEST_METHOD(TwoTrickSameManipTest_3_TurnAfterFirst)
		{
			float startingAngle = 5.8857827f; // library start
			float zoomSensThatWorks = 1.5f; // will check against
			// then do one dot right 
			float targetAngle1 = 5.1400619f; // and you can reach this angle
			// then do 2 dots left and 1 clockwise turn
			float targetAngle2 = 5.3216538f; // and you can reach this angle

			float viewAngleIncrement = viewAngleIncrementFinder(6.8f);

			auto zoomSensResult = calcZoomSensManip(viewAngleIncrementFinder(6.8f), startingAngle, targetAngle1, targetAngle2, 2, 0, -1, 5);
			Assert::IsFalse(zoomSensResult.empty(), L"Not enough results! No manips calculated");


			std::stringstream ss;
			for (auto& manip : zoomSensResult)
			{
				ss << manip << std::endl;
				if (manip.DotsToFirstAngle == -1 && manip.SecondAngleExtraDots == 2)
				{
					if (manip.ZoomSensitivityValue == zoomSensThatWorks)
						return; // Test passed!

					// calculated zs may be different from what we used but still actually have the same result!
					// so test for being within 1%
					float differenceFromUsedValue = std::abs(zoomSensThatWorks - manip.ZoomSensitivityValue);
					if (differenceFromUsedValue / zoomSensThatWorks < 0.01)
						return; // Test passed!
					else
						Assert::Fail((StringToWString(std::format("Manip found with correct dots but incorrect sensitivity value. Expected: <{}> Actual: <{}>", zoomSensThatWorks, manip.ZoomSensitivityValue))).c_str());
				}
			}




			Assert::Fail(StringToWString(std::format("Reproduction manip not found! But we did find: \n{}", ss.str())).c_str());
		}


		TEST_METHOD(TwoTrickSameManipTest_4_TurnBeforeBoth)
		{
			float startingAngle = 5.8857827f; // library start
			float zoomSensThatWorks = 1.5f; // will check against
			// then do one dot right & 1 counter clockwise turn
			float targetAngle1 = 1.6554151f; // and you can reach this angle
			// then do 2 dots left and 2 more counter clockwise turns
			float targetAngle2 = 2.6755407f; // and you can reach this angle

			float viewAngleIncrement = viewAngleIncrementFinder(6.8f);

			auto zoomSensResult = calcZoomSensManip(viewAngleIncrementFinder(6.8f), startingAngle, targetAngle1, targetAngle2, 2, 1, 3, 5);
			Assert::IsFalse(zoomSensResult.empty(), L"Not enough results! No manips calculated");


			std::stringstream ss;
			for (auto& manip : zoomSensResult)
			{
				ss << manip << std::endl;
				if (manip.DotsToFirstAngle == -1 && manip.SecondAngleExtraDots == 2)
				{
					if (manip.ZoomSensitivityValue == zoomSensThatWorks)
						return; // Test passed!

					// calculated zs may be different from what we used but still actually have the same result!
					// so test for being within 1%
					float differenceFromUsedValue = std::abs(zoomSensThatWorks - manip.ZoomSensitivityValue);
					if (differenceFromUsedValue / zoomSensThatWorks < 0.01)
						return; // Test passed!
					else
						Assert::Fail((StringToWString(std::format("Manip found with correct dots but incorrect sensitivity value. Expected: <{}> Actual: <{}>", zoomSensThatWorks, manip.ZoomSensitivityValue))).c_str());
				}
			}




			Assert::Fail(StringToWString(std::format("Reproduction manip not found! But we did find: \n{}", ss.str())).c_str());
		}
	};
}
