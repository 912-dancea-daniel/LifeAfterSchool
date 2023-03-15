#include <iostream>
#include "ui.h"
//#include "test.h"
#include <windows.h>
#include <shellapi.h>
//#include "test.h"
#include <limits>
#include "myexc.h"
#undef max
#include "a14.h"




ui::ui()
{
	this->serv = Service();
}

ui::~ui()
{
	return;
}

void ui::printMenu()
{
	std::cout << "1. Add new event\n";
	std::cout << "2. Remove event\n";
	std::cout << "3. Update event\n";
	std::cout << "4. Print all events\n";
	std::cout << "5. Set repo from file\n";
	std::cout << "6. Exit\n\n";
}


void ui::printEvents()
{
	EventVector tmp = this->serv.getData();

	if (tmp.getEventLen() == 0)
	{
		std::cout << "The event list is empty\n";
		return;
	}

	for (int i = 0; i < tmp.getEventLen(); i++)
	{
		std::cout << i + 1 << "\n";
		std::cout << "The title: " << tmp.getEvent(i).getTitle() << "\nThe description: " << tmp.getEvent(i).getDescription();
		std::cout << "\nThe link: " << tmp.getEvent(i).getLink() << "\nThe nr of people: " << tmp.getEvent(i).getNumberOfPeople();
		std::cout << "\nThe Date: " << tmp.getEvent(i).getDate().getDay() << "/" << tmp.getEvent(i).getDate().getMonth() << "/" << tmp.getEvent(i).getDate().getYear();
		std::cout << "\nThe hour: " << tmp.getEvent(i).getDate().getHour() << ":" << tmp.getEvent(i).getDate().getMinute() << "\n\n";
	}
}

void ui::printUserMenu()
{
	std::cout << "1. Print the events\n";
	std::cout << "2. Print your events\n";
	std::cout << "3. Delete an event\n";
	std::cout << "4. Print the CSV or HTML file\n";
	std::cout << "5. Exit\n";
}

void ui::printUserEvents(int opt)
{
	if (opt == 1)
	{
		CSV tmp;
		tmp = this->serv.getCSVUser();
		for (int i = 0; i < tmp.getEventLen(); i++)
		{
			std::cout << i + 1 << "\n";
			std::cout << "The title: " << tmp.getEvent(i).getTitle() << "\nThe description: " << tmp.getEvent(i).getDescription();
			std::cout << "\nThe link: " << tmp.getEvent(i).getLink() << "\nThe nr of people: " << tmp.getEvent(i).getNumberOfPeople();
			std::cout << "\nThe Date: " << tmp.getEvent(i).getDate().getDay() << "/" << tmp.getEvent(i).getDate().getMonth() << "/" << tmp.getEvent(i).getDate().getYear();
			std::cout << "\nThe hour: " << tmp.getEvent(i).getDate().getHour() << ":" << tmp.getEvent(i).getDate().getMinute() << "\n\n";
		}
	}

	else if (opt == 2)
	{
		forHTML tmp;
		tmp = this->serv.getHTMLUser();
		for (int i = 0; i < tmp.getEventLen(); i++)
		{
			std::cout << i + 1 << "\n";
			std::cout << "The title: " << tmp.getEvent(i).getTitle() << "\nThe description: " << tmp.getEvent(i).getDescription();
			std::cout << "\nThe link: " << tmp.getEvent(i).getLink() << "\nThe nr of people: " << tmp.getEvent(i).getNumberOfPeople();
			std::cout << "\nThe Date: " << tmp.getEvent(i).getDate().getDay() << "/" << tmp.getEvent(i).getDate().getMonth() << "/" << tmp.getEvent(i).getDate().getYear();
			std::cout << "\nThe hour: " << tmp.getEvent(i).getDate().getHour() << ":" << tmp.getEvent(i).getDate().getMinute() << "\n\n";
		}
	}
	else
	{
		EventVector tmp;
		tmp = this->serv.getUserRepo();
		for (int i = 0; i < tmp.getEventLen(); i++)
		{
			std::cout << i + 1 << "\n";
			std::cout << "The title: " << tmp.getEvent(i).getTitle() << "\nThe description: " << tmp.getEvent(i).getDescription();
			std::cout << "\nThe link: " << tmp.getEvent(i).getLink() << "\nThe nr of people: " << tmp.getEvent(i).getNumberOfPeople();
			std::cout << "\nThe Date: " << tmp.getEvent(i).getDate().getDay() << "/" << tmp.getEvent(i).getDate().getMonth() << "/" << tmp.getEvent(i).getDate().getYear();
			std::cout << "\nThe hour: " << tmp.getEvent(i).getDate().getHour() << ":" << tmp.getEvent(i).getDate().getMinute() << "\n\n";
		}
	}

	
}


/*
int main(int argc, char* argv[])
{

	ui UI = ui();
	int opt = 1, day, month, year, hour, minutes, nrOfPeople;
	
	std::string title, link, desc;

	QApplication a(argc, argv);
	qt_a11 gui;
	std::vector<Event> v;
	v.push_back(Event{ "no", "no", "n", 1, Date{1,1,2022, 2, 2} });

	v.push_back(Event{ "b", "b", "b", 1, Date{1,1,2022, 2, 2} });
	EventVector tmp = UI.serv.getData();


	for (int i = 0; i < tmp.getEventLen(); i++)
	{
		v.push_back(Event{ tmp.getEvent(i).getTitle(), tmp.getEvent(i).getDescription(), tmp.getEvent(i).getLink(), tmp.getEvent(i).getNumberOfPeople(), tmp.getEvent(i).getDate() });
	}

	gui.innit(v);



	QWidget* user = new QWidget{};
	QHBoxLayout* userBox = new QHBoxLayout{};
	user->setLayout(userBox);
	QTextEdit* userInputList = new QTextEdit{};
	userInputList->setReadOnly(true);
	for (int i(0); i < UI.serv.getData().getEventLen(); i++) {
		userInputList->append(QString::number(i + 1));
		userInputList->append(QString(UI.serv.getData().arr[i].getTitle().c_str()));
		userInputList->append(QString(UI.serv.getData().arr[i].getDescription().c_str()));
		userInputList->append(QString(UI.serv.getData().arr[i].getLink().c_str()));
		userInputList->append(QString::number(UI.serv.getData().arr[i].getDate().getDay()));
		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString("."));
		userInputList->moveCursor(QTextCursor::End);
		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString::number(UI.serv.getData().arr[i].getDate().getMonth()));
		userInputList->moveCursor(QTextCursor::End);

		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString("."));
		userInputList->moveCursor(QTextCursor::End);
		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString::number(UI.serv.getData().arr[i].getDate().getYear()));
		userInputList->moveCursor(QTextCursor::End);

		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString(" "));
		userInputList->moveCursor(QTextCursor::End);
		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString::number(UI.serv.getData().arr[i].getDate().getHour()));
		userInputList->moveCursor(QTextCursor::End);

		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString(":"));
		userInputList->moveCursor(QTextCursor::End);
		userInputList->moveCursor(QTextCursor::End);
		userInputList->insertPlainText(QString::number(UI.serv.getData().arr[i].getDate().getMinute()));
		userInputList->moveCursor(QTextCursor::End);

		userInputList->append(QString::number(UI.serv.getData().arr[i].getNumberOfPeople()));
		userInputList->append(QString("\n"));
	}
	QVBoxLayout* hlUser = new QVBoxLayout{};
	QPushButton* addUser = new QPushButton{ "&Add new event" };
	QPushButton* removeUser = new QPushButton{ "&Remove an event" };
	//QPushButton* updateUser = new QPushButton{ "&Open " };
	hlUser->addWidget(addUser);
	hlUser->addWidget(removeUser);
	



	


	return a.exec();


	std::cout << "\n\nDo you want to start in admin mode (1) or user mode(2)?\n";

	std::cin >> opt;

	if (opt == 1)
	{


		UI.serv.getData().writeToFile("out.txt");
		
		while (1)
		{
			UI.printMenu();

			std::cin >> opt;

			if (std::cin.fail())
			{
				std::cout << "NOTVALID";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{
				if (opt == 1)
				{
					std::cout << "Please enter the title of the event: ";
					std::cin >> title;

					std::cout << "Please enter the description of the event: ";
					std::cin >> desc;

					std::cout << "Please enter the link of the event: ";
					std::cin >> link;

					std::cout << "Please enter the day of the event: ";
					std::cin >> day;

					if (std::cin.fail())
					{
						std::cout << "Enter a valid day";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					else
					{

						std::cout << "Please enter the month of the event: ";
						std::cin >> month;

						if (std::cin.fail())
						{
							std::cout << "Enter a valid month";
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
						else
						{
							std::cout << "Please enter the year of the event: ";
							std::cin >> year;

							if (std::cin.fail())
							{
								std::cout << "Enter a valid year";
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
							else
							{

								std::cout << "Please enter the hour of the event: ";
								std::cin >> hour;

								if (std::cin.fail())
								{
									std::cout << "Enter a valid hour";
									std::cin.clear();
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}
								else
								{
									std::cout << "Please enter the minute of the event: ";
									std::cin >> minutes;

									if (std::cin.fail())
									{
										std::cout << "Enter a valid minute";
										std::cin.clear();
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
									else
									{
										std::cout << "Please enter the number of people who will participate: ";
										std::cin >> nrOfPeople;

										if (std::cin.fail())
										{
											std::cout << "Enter a valid number";
											std::cin.clear();
											std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
										}
										else
										{
											try
											{
												UI.serv.addEvent(title, desc, link, nrOfPeople, day, month, year, hour, minutes);
												UI.serv.getData().writeToFile("out.txt");
								
												UI.printEvents();
											}
											catch (Exception& ex)
											{
												std::cout << ex.what();
											}

										}
									}
								}

							}

						}

					}

				}

				else if (opt == 2)
				{

					std::cout << "Enter the data of the event you want to delete\nTitle of the event: ";
					std::cin >> title;

					std::cout << "Day of the event: ";
					std::cin >> day;

					if (std::cin.fail())
					{
						std::cout << "Enter a valid day";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					else
					{

						std::cout << "Please enter the month of the event: ";
						std::cin >> month;

						if (std::cin.fail())
						{
							std::cout << "Enter a valid month";
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
						else
						{
							std::cout << "Please enter the year of the event: ";
							std::cin >> year;

							if (std::cin.fail())
							{
								std::cout << "Enter a valid year";
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
							else
							{

								std::cout << "Please enter the hour of the event: ";
								std::cin >> hour;

								if (std::cin.fail())
								{
									std::cout << "Enter a valid hour";
									std::cin.clear();
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}
								else
								{
									std::cout << "Please enter the minute of the event: ";
									std::cin >> minutes;

									if (std::cin.fail())
									{
										std::cout << "Enter a valid minute";
										std::cin.clear();
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
									else
									{
										try
										{
											UI.serv.deleteEvent(title, day, month, year, hour, minutes);
											UI.serv.getData().writeToFile("out.txt");
										}
										catch (Exception& ex)
										{
											std::cout << ex.what();
										}

										UI.printEvents();

									}
								}
							}
						}
					}

				}
				else if (opt == 3)
				{
					std::cout << "Enter the data of the event you want to update\nTitle of the event: ";
					std::cin >> title;

					std::cout << "Day of the event: ";
					std::cin >> day;

					if (std::cin.fail() || day == -1)
					{
						std::cout << "Enter a valid day";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					else
					{

						std::cout << "Please enter the month of the event: ";
						std::cin >> month;

						if (std::cin.fail() || month == -1)
						{
							std::cout << "Enter a valid month";
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
						else
						{
							std::cout << "Please enter the year of the event: ";
							std::cin >> year;

							if (std::cin.fail() || year == -1)
							{
								std::cout << "Enter a valid year";
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
							else
							{

								std::cout << "Please enter the hour of the event: ";
								std::cin >> hour;

								if (std::cin.fail() || hour == -1)
								{
									std::cout << "Enter a valid hour";
									std::cin.clear();
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}
								else
								{
									std::cout << "Please enter the minute of the event: ";
									std::cin >> minutes;

									if (std::cin.fail() || minutes == -1)
									{
										std::cout << "Enter a valid minute";
										std::cin.clear();
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
									else
									{
										std::cout << "What do you want to update? \n1. The title\n2.The description\n3.The link\n4.The number of people\n5.The date\n";

										std::cin >> opt;

										if (opt == 1)
										{
											std::string tmp;
											std::cout << "Enter the new title: ";
											std::cin >> tmp;
											try
											{
												UI.serv.updateTitle(title, day, month, year, hour, minutes, tmp);
												UI.serv.getData().writeToFile("out.txt");
											}
											catch (Exception& ex)
											{
												std::cout << ex.what();
											}

										}
										else if (opt == 2)
										{
											std::string tmp;
											std::cout << "Enter the new description: ";
											std::cin >> tmp;
											try
											{
												UI.serv.updateDesc(title, day, month, year, hour, minutes, tmp);
												UI.serv.getData().writeToFile("out.txt");
											}
											catch (Exception& ex)
											{
												std::cout << ex.what();
											}
										}
										else if (opt == 3)
										{
											std::string tmp;
											std::cout << "Enter the new link: ";
											std::cin >> tmp;

											try
											{
												UI.serv.updateLink(title, day, month, year, hour, minutes, tmp);
												UI.serv.getData().writeToFile("out.txt");
											}
											catch (Exception& ex)
											{
												std::cout << ex.what();
											}

										}
										else if (opt == 4)
										{
											int tmp;
											std::cout << "Enter the new number of people: ";
											std::cin >> tmp;
											if (std::cin.fail())
											{
												std::cout << "Enter a valid number";
												std::cin.clear();
												std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
											}
											else
											{
												try
												{
													UI.serv.updateNrOfPeople(title, day, month, year, hour, minutes, tmp);
													UI.serv.getData().writeToFile("out.txt");
												}
												catch (Exception& ex)
												{
													std::cout << ex.what();
												}

											}

										}
										else if (opt == 5)
										{
											int newDay, newMonth, newYear, newHour, newMinute;
											std::cout << "Enter the new date\nThe day";
											std::cin >> newDay;

											if (std::cin.fail())
											{
												std::cout << "Enter a valid day";
												std::cin.clear();
												std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
											}
											else
											{
												std::cout << "The month: ";
												std::cin >> newMonth;
												if (std::cin.fail())
												{
													std::cout << "Enter a valid month";
													std::cin.clear();
													std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
												}
												else
												{
													std::cout << "The year: ";
													std::cin >> newYear;
													if (std::cin.fail())
													{
														std::cout << "Enter a valid year";
														std::cin.clear();
														std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
													}
													else
													{
														std::cout << "The hour: ";
														std::cin >> newHour;
														if (std::cin.fail())
														{
															std::cout << "Enter a valid hour";
															std::cin.clear();
															std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
														}
														else
														{
															std::cout << "The minute: ";
															std::cin >> newMinute;
															if (std::cin.fail())
															{
																std::cout << "Enter a valid minute";
																std::cin.clear();
																std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
															}
															else
															{
																try
																{
																	UI.serv.updateDate(title, day, month, year, hour, minutes, newDay, newMonth, newYear, newHour, newMinute);
																	UI.serv.getData().writeToFile("out.txt");
																	UI.printEvents();
																}
																catch (Exception& ex)
																{
																	std::cout << ex.what();
																}
															}

														}

													}
												}
											}
										}

									}
								}
							}
						}
					}

				}
				else if (opt == 4)
				{
					UI.printEvents();
				}
				else if (opt == 5)
				{
					std::string fileName;
					std::cout << "Add the file name: ";
					std::cin >> fileName;
					UI.serv.setRepoFromFile(fileName);
				}
				else if (opt == 6)
				{
					//destroying
					return 0;
				}
			}
		}

		return 0;
	}
	else if (opt == 2)
	{
		int startIndex = 0, endIndex = 0;
		std::cout << "In which format do you want to save the events?\n1.CSV or 2. HTML?\n";
		int nrFile = 0;
		std::cin >> nrFile;
		while (1)
		{
			UI.printUserMenu();
			std::cin >> opt;

			if (opt == 1)
			{
				std::cout << "Input month (or 0 for all): ";
				std::cin >> opt;

				UI.serv.getEvents(startIndex, endIndex, opt);

				for (int i = startIndex; i < endIndex; i++)
				{
					std::cout << "The title: " << UI.serv.getEvent(i).getTitle();
					std::cout << "\nThe link: " << UI.serv.getEvent(i).getLink() << "\nThe nr of people: " << UI.serv.getEvent(i).getNumberOfPeople();
					std::cout << "\nThe Date: " << UI.serv.getEvent(i).getDate().getDay() << "/" << UI.serv.getEvent(i).getDate().getMonth() << "/" << UI.serv.getEvent(i).getDate().getYear();
					std::cout << "\nThe hour: " << UI.serv.getEvent(i).getDate().getHour() << ":" << UI.serv.getEvent(i).getDate().getMinute() << "\n\n";

					system(std::string("start " + UI.serv.getEvent(i).getLink()).c_str());

					std::cout << "Press 1 for adding to your event list, or 2 for not (and continue to the next event) or 3 for exit: ";
					std::cin >> opt;

					if (opt == 1)
					{
						try
						{
							UI.serv.addUserEvent(i, nrFile);
						}
						catch (Exception& ex)
						{
							std::cout << ex.what();
						}
					}
					else if (opt == 3)
					{

						if (nrFile == 2)
						{
							UI.serv.getHTMLUser().writeToFile("outHTML.html");
							
						}
						else
						if (nrFile == 1)
						{
							UI.serv.getCSVUser().writeToFile("outCSV.csv");
						}


						break;

					}

					if (i == endIndex - 1)
						i = startIndex - 1;

				}
			}
			else if (opt == 2)
			{
				UI.printUserEvents(nrFile);
			}
			else if (opt == 3)
			{
				std::cout << "Enter the index of the event you want to delete from your list: ";
				std::cin >> opt;

				if (std::cin.fail())
				{
					std::cout << "Enter a valid index";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else
				{
					try
					{
						UI.serv.deleteUserEvent(opt, nrFile);
					}
					catch (Exception& ex)
					{
						std::cout << ex.what();
					}

				}
				UI.printUserEvents(nrFile);
			}
			else if (opt == 4)
			{
				if (nrFile == 2)
				{
					UI.serv.getHTMLUser().openFile("outHTML.html");

				}
				else
				if (nrFile == 1)
				{
					UI.serv.getCSVUser().openFile("outCSV.csv");
				}
			}
			else if (opt == 5)
			{
				break;
			}
		}

	}
	return 0;
}
*/