/* Evan Nuss and Noah Pittenger, Section 1, nussevan@gmail.com and noahap@byu.edu
We exclusively used Visual Studio to build this program.
We used pair programming to build this program.
Test Case #1:
Inputs: Selection-1, slot number-4
Outputs: Path: [4.0, 4.5, 4.0, 4.5, 4.0, 4.5, 5.0, 4.5, 4.0, 4.5, 5.0, 5.5, 5.0]
Winnings: $0.00
Test case #2:
Inputs: Selection:-1, 2, number of chips: 9, slot number: 7
Outputs: Total winnings on 9 chips: $4300.00
Average winnings per chip: $477.78
Test Case #3:
Inputs: Selection: 2, number of chips: -12, Selection: 2, number of chips: 98, Slot number: -3, selection: 2, number of chips: 98, slot number: 5
Outputs: Total winnings on 98 chips: $249500.00
Average winnings per chip: $2545.92
*/
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main() {
	const int DROP_ONE_CHIP = 1;
	const int DROP_MULTIPLE_CHIPS = 2;
	const int SHOW_MENU = 3;
	const int QUIT_GAME = 4;

	const int RIGHT_EDGE = 8;
	const int LEFT_EDGE = 0;

	const int PATH_PRECISION = 1;
	const int WINNINGS_PRECISION = 2;
	const int SLOT_PRECISION = 0;

	const int GRAND_PRIZE = 10000;
	const int LARGE_PRIZE = 1000;
	const int MEDIUM_PRIZE = 500;
	const int SMALL_PRIZE = 100;
	const int LOSER_PRIZE = 0;

	const int NUM_ROWS = 12;

	const int RANDOM_RIGHT = 1;
	const int RANDOM_PATH_NUMBER = 2;

	const int END_OF_PATH_OUTPUT = 11;

	const int CONSTANT_SEED = 42;
	srand(CONSTANT_SEED);
	const double SHIFT_LEFT = -.5;
	const double SHIFT_RIGHT = .5;



	int userSelection = 0;
	cout << "Welcome to the Plinko simulator! Enter 3 to see options." << endl;
	cout << endl;
	cout << "Enter your selection now:" << endl;
	cin >> userSelection;
	cout << endl;
	while (userSelection != QUIT_GAME) {
		if ((userSelection < DROP_ONE_CHIP) || (userSelection > QUIT_GAME)) {
			cout << endl;
			cout << "Invalid selection. Enter 3 to see options." << endl;
			cout << endl;
			cout << "Enter your selection now:" << endl;
			cin >> userSelection;

		}
		else if (userSelection == DROP_ONE_CHIP) {
			double singleChipWinnings = 0.0;
			double slotNum = 0.0;

			cout << "*** Drop a single chip ***" << endl;
			cout << endl;
			cout << "Which slot do you want to drop the chip in (0-8)?";
			cin >> slotNum;
			cout << endl;
			while ((slotNum < LEFT_EDGE) || (slotNum > RIGHT_EDGE)) {
				cout << "Invalid slot." << endl;
				cout << endl;
				cout << "Enter your selection now: " << endl;

				cin >> userSelection;
				if (userSelection == DROP_ONE_CHIP) {
					cout << "*** Drop a single chip ***" << endl;
					cout << endl;
					cout << "Which slot do you want to drop the chip in (0-8)?";
					cin >> slotNum;
					cout << endl;
				}
				else if ((userSelection == DROP_MULTIPLE_CHIPS) || (userSelection == SHOW_MENU) || (userSelection == QUIT_GAME)) {
					continue;
				}
			}
			cout << "*** Dropping chip into slot " << fixed << setprecision(SLOT_PRECISION) << slotNum << " ***" << endl;
			cout << "Path: [" << fixed << setprecision(PATH_PRECISION) << slotNum << ", ";
			double chipPosition = 0;
			for (int i = 0; i < NUM_ROWS; i++) {
				double randomNumber = 0;
				if (slotNum == LEFT_EDGE) {
					chipPosition = slotNum + SHIFT_RIGHT;
				}
				else if (slotNum == RIGHT_EDGE) {
					chipPosition = slotNum + SHIFT_LEFT;
				}
				else {
					randomNumber = (rand() % RANDOM_PATH_NUMBER);
					if (randomNumber < RANDOM_RIGHT) {
						chipPosition = slotNum + SHIFT_LEFT;
					}
					else {
						chipPosition = slotNum + SHIFT_RIGHT;
					}
				}
				cout << fixed << setprecision(PATH_PRECISION) << chipPosition;
				slotNum = chipPosition;

				if (i < END_OF_PATH_OUTPUT) {
					cout << ", ";
				}
			}
			cout << "]" << endl;

			switch (static_cast<int>(slotNum)) {
			case 0:
				singleChipWinnings = SMALL_PRIZE;
				break;
			case 1:
				singleChipWinnings = MEDIUM_PRIZE;
				break;
			case 2:
				singleChipWinnings = LARGE_PRIZE;
				break;
			case 3:
				singleChipWinnings = LOSER_PRIZE;
				break;
			case 4:
				singleChipWinnings = GRAND_PRIZE;
				break;
			case 5:
				singleChipWinnings = LOSER_PRIZE;
				break;
			case 6:
				singleChipWinnings = LARGE_PRIZE;
				break;
			case 7:
				singleChipWinnings = MEDIUM_PRIZE;
				break;
			case 8:
				singleChipWinnings = SMALL_PRIZE;
				break;
			}

			cout << "Winnings: $" << fixed << setprecision(WINNINGS_PRECISION) << singleChipWinnings << endl;

			cout << "Enter your selection now:" << endl;
			cin >> userSelection;
		}



		else if (userSelection == DROP_MULTIPLE_CHIPS) {
			double newChipSlotNum = 0.0;
			double multipleChipWinnings = 0.0;
			double initialSlotNum = 0.0;
			int numChips = 0;
			cout << "*** Drop multiple chips ***" << endl;
			cout << endl;
			cout << "How many chips do you want to drop (>0)?" << endl;
			cin >> numChips;
			if (numChips > 0) {

				cout << "Which slot do you want to drop the chip in (0-8)?";
				cin >> initialSlotNum;
				cout << endl;
				newChipSlotNum = initialSlotNum;
				if ((initialSlotNum >= LEFT_EDGE) && (initialSlotNum <= RIGHT_EDGE)) {
					cout << endl;
					double newChipSlotNum = 0;
					for (int j = 0; j < numChips; j++) {
						newChipSlotNum = initialSlotNum;
						for (int i = 0; i < NUM_ROWS; i++) {
							double randomNumber = 0;
							if (newChipSlotNum == LEFT_EDGE) {
								newChipSlotNum += SHIFT_RIGHT;
							}
							else if (newChipSlotNum == RIGHT_EDGE) {
								newChipSlotNum += SHIFT_LEFT;
							}
							else {
								randomNumber = (rand() % RANDOM_PATH_NUMBER);
								if (randomNumber < RANDOM_RIGHT) {
									newChipSlotNum += SHIFT_LEFT;
								}
								else {
									newChipSlotNum += SHIFT_RIGHT;
								}
							}
						}

						switch (static_cast<int>(newChipSlotNum)) {
						case 0:
							multipleChipWinnings += SMALL_PRIZE;
							break;
						case 1:
							multipleChipWinnings += MEDIUM_PRIZE;
							break;
						case 2:
							multipleChipWinnings += LARGE_PRIZE;
							break;
						case 3:
							multipleChipWinnings += LOSER_PRIZE;
							break;
						case 4:
							multipleChipWinnings += GRAND_PRIZE;
							break;
						case 5:
							multipleChipWinnings += LOSER_PRIZE;
							break;
						case 6:
							multipleChipWinnings += LARGE_PRIZE;
							break;
						case 7:
							multipleChipWinnings += MEDIUM_PRIZE;
							break;
						case 8:
							multipleChipWinnings += SMALL_PRIZE;
							break;
						}
					}
					cout << "Total winnings on " << numChips << " chips: $" << fixed << setprecision(WINNINGS_PRECISION) << multipleChipWinnings << endl;
					cout << "Average winnings per chip: $";
					double averageChipWinnings = 0.0;
					averageChipWinnings = (multipleChipWinnings / numChips);
					cout << fixed << setprecision(WINNINGS_PRECISION) << averageChipWinnings << endl;
					cout << endl;




				}
				else {
					cout << "Invalid slot." << endl;
				}
			}
			else {
				cout << "Invalid number of chips." << endl;
			}
			cout << "Enter your selection now:" << endl;
			cin >> userSelection;
			cout << endl;
		}


		else {
			cout << "Menu: Please select one of the following options :" << endl;
			cout << endl;

			cout << "1 - Drop a single chip into one slot" << endl;
			cout << "2 - Drop multiple chips into one slot" << endl;
			cout << "3 - Show the options menu" << endl;
			cout << "4 - Quit the program" << endl;
			cout << endl;

			cout << "Enter your selection now:" << endl;
			cin >> userSelection;

		}
	}
	if (userSelection == QUIT_GAME) {
		cout << "Goodbye!" << endl;
	}

	system("pause");


	return 0;
}