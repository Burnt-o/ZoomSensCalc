
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
			auto zoomSensResult = calcZoomSensManip(viewAngleIncrement, startingAngle, targetAngle, targetAngle, 2, counterClockwiseTurns, 5);

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
			auto zoomSensResult = calcZoomSensManip(viewAngleIncrement, startingAngle, targetAngle, targetAngle, 2, counterClockwiseTurns, 5);
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
			ZoomSensManipCalc_MatchesSpreadsheet(viewAngleIncrementFinder(6.8f), 5.3184395f, 3.4001875f, -1, 1.95533666f, 2, -1);
		}

		TEST_METHOD(ZoomSensManip_343_RS3_ActuallyWorks)
		{
			DoesCalculatedZoomSensManipActuallyWork(viewAngleIncrementFinder(6.8f), 5.3184395f, 3.4001875f, 2, -1);
		}


	
	};
}
