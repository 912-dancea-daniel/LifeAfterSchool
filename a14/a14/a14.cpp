#include "a14.h"
#include <qmessagebox.h>

a14::a14(QWidget *parent)
    : QMainWindow(parent)
{
	//setFocusPolicy(Qt::StrongFocus);
    ui1.setupUi(this);
	setFocusPolicy(Qt::StrongFocus);
	//this->tableModel = EventTable{ UI.serv.repo };
}


void a14::innit()
{
	wnd = new QWidget{};
	vL = new QHBoxLayout{};
	wnd->setLayout(vL);


	QVBoxLayout* hL1 = new QVBoxLayout{};
	QWidget* actions1 = new QWidget{};


	edit = new QTextEdit{};
	QObject::connect(edit, &QTextEdit::textChanged, this, &a14::changeCaption);
	txt = new QTextEdit();
	txt->setFixedWidth(250);

	actions1->setLayout(hL1);
	txt->setReadOnly(true);
	hL1->addWidget(edit);
	hL1->addWidget(txt);
	edit->setFixedHeight(30);

	edit->setFixedWidth(250);

	setList();


	updatePage = new QWidget{};



	QVBoxLayout* updateVl = new QVBoxLayout{};
	updatePage->setLayout(updateVl);


	updateTitleButton = new QPushButton{ "Update title" };
	connect(updateTitleButton, &QPushButton::clicked, this, &a14::updateTitle);
	updateVl->addWidget(updateTitleButton);

	updateDescButton = new QPushButton{ "Update desc" };
	connect(updateDescButton, &QPushButton::clicked, this, &a14::updateDesc);
	updateVl->addWidget(updateDescButton);

	updateNrOfPeopleButton = new QPushButton{ "Update number of people" };
	connect(updateNrOfPeopleButton, &QPushButton::clicked, this, &a14::updateNr);
	updateVl->addWidget(updateNrOfPeopleButton);

	updateLinkButton = new QPushButton{ "Update link" };
	connect(updateLinkButton, &QPushButton::clicked, this, &a14::updateLink);
	updateVl->addWidget(updateLinkButton);

	updateDateButton = new QPushButton{ "Update Date" };
	connect(updateDateButton, &QPushButton::clicked, this, &a14::updateDate);
	updateVl->addWidget(updateDateButton);




	boxes = new QWidget{};

	fL = new QFormLayout{};
	//details->setLayout(fL);

	QVBoxLayout* hL = new QVBoxLayout{};
	QPushButton* add = new QPushButton{ "&Add" };
	QPushButton* remove = new QPushButton{ "&Remove" };
	QPushButton* update = new QPushButton{ "&Update" };
	undoButton = new QPushButton{ "&Undo" };
	redoButton = new QPushButton{ "&Redo" };
	hL->addWidget(add);
	hL->addWidget(remove);
	hL->addWidget(update);
	hL->addWidget(undoButton);
	hL->addWidget(redoButton);
	boxes->setLayout(fL);


	connect(undoButton, &QPushButton::clicked, this, &a14::performUndo);
	connect(redoButton, &QPushButton::clicked, this, &a14::performRedo);

	labelName = new QLabel{ "&Title" };
	textBoxTitle = new QLineEdit{};
	labelName->setBuddy(textBoxTitle);
	fL->addRow(labelName, textBoxTitle);

	QLabel* labelDesc = new QLabel{ "&Description" };
	textBoxDesc = new QLineEdit{};
	labelDesc->setBuddy(textBoxDesc);
	fL->addRow(labelDesc, textBoxDesc);

	QLabel* labelLink = new QLabel{ "&Link" };
	textBoxLink = new QLineEdit{};
	labelLink->setBuddy(textBoxLink);
	fL->addRow(labelLink, textBoxLink);

	QLabel* labelNrOfPoeple = new QLabel{ "&Number of poeple" };
	textBoxNrOfPeople = new QLineEdit{};
	labelNrOfPoeple->setBuddy(textBoxNrOfPeople);
	fL->addRow(labelNrOfPoeple, textBoxNrOfPeople);

	QLabel* labelDay = new QLabel{ "&Day" };
	textBoxDay = new QLineEdit{};
	labelDay->setBuddy(textBoxDay);
	fL->addRow(labelDay, textBoxDay);

	QLabel* labelMonth = new QLabel{ "&Month" };
	textBoxMonth = new QLineEdit{};
	labelMonth->setBuddy(textBoxMonth);
	fL->addRow(labelMonth, textBoxMonth);

	QLabel* labelYear = new QLabel{ "&Year" };
	textBoxYear = new QLineEdit{};
	labelYear->setBuddy(textBoxYear);
	fL->addRow(labelYear, textBoxYear);

	QLabel* labelHour = new QLabel{ "&Hour" };
	textBoxHour = new QLineEdit{};
	labelHour->setBuddy(textBoxHour);
	fL->addRow(labelHour, textBoxHour);

	QLabel* labelMinute = new QLabel{ "&Minute" };
	textBoxMinute = new QLineEdit{};
	labelMinute->setBuddy(textBoxMinute);
	fL->addRow(labelMinute, textBoxMinute);


	QWidget* actions = new QWidget{};
	actions->setLayout(hL);

	//showMyBarChart = new QPushButton{"Show bar chart"};

	eventButton = new QPushButton{ "&Add the event" };
	fL->addWidget(eventButton);
	//fL->addWidget(showMyBarChart);



	connect(add, &QPushButton::clicked, this, &a14::addNewEvent);
	connect(update, &QPushButton::clicked, this, &a14::updateEvent);
	connect(remove, &QPushButton::clicked, this, &a14::removeEvent);

	//connect(showMyBarChart, &QPushButton::clicked, this, &qt_a11::showTheBarChart);

	//vL->addWidget(txt);
	//vL->addWidget(edit);
	//vL->addWidget(boxes);


	vL->addWidget(actions1);
	vL->addWidget(actions);



	undoShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	connect(undoShortCut, &QShortcut::activated, this, &a14::performUndo);

	QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_F2), this, SLOT(performUndo()));
	shortcut->setAutoRepeat(false);

	//QAction* foo = new QAction(this);
	//foo->setShortcut(Qt::CTRL | Qt::Key_Z);

	//connect(foo, SIGNAL(triggered()), this, SLOT(performUndo()));
	//this->addAction(foo);

	// create shortcut
	//undoShortCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this);

	//// connect its 'activated' signal to your function 'foo'
	//QObject::connect(undoShortCut, &QShortcut::activated, this, &a14::performUndo);

	wnd->show();

	setFocusPolicy(Qt::StrongFocus);


}

void a14::changeCaption()
{
	this->txt->append("nono");

	std::vector<Event> l;

	EventVector tmp = UI.serv.getData();

	txt->clear();

	for (int i = 0; i < tmp.getEventLen(); i++)
	{
		l.push_back(Event{ tmp.getEvent(i).getTitle(), tmp.getEvent(i).getDescription(), tmp.getEvent(i).getLink(), tmp.getEvent(i).getNumberOfPeople(), tmp.getEvent(i).getDate() });
	}

	std::vector<Event> my{};
	for (int i = 0; i < l.size(); i++)
	{
		if (l[i].getTitle().find(this->edit->toPlainText().toStdString()) != std::string::npos)
		{
			my.push_back(l[i]);
		}
		else if (l[i].getDescription().find(this->edit->toPlainText().toStdString()) != std::string::npos)
		{
			my.push_back(l[i]);

		}
		//		if(l[i].getTitle().find(this->edit->toPlainText()) != std::string::npos))

	}
	this->txt->clear();

	for (int i = 0; i < my.size(); i++)
	{
		txt->append(QString::number(i + 1));
		txt->append(QString(my[i].getTitle().c_str()));
		txt->append(QString(my[i].getDescription().c_str()));
		txt->append(QString(my[i].getLink().c_str()));
		txt->append(QString::number(my[i].getDate().getDay()));
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString("."));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(my[i].getDate().getMonth()));
		txt->moveCursor(QTextCursor::End);

		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString("."));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(my[i].getDate().getYear()));
		txt->moveCursor(QTextCursor::End);

		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString(" "));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(my[i].getDate().getHour()));
		txt->moveCursor(QTextCursor::End);

		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString(":"));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(my[i].getDate().getMinute()));
		txt->moveCursor(QTextCursor::End);

		txt->append(QString::number(my[i].getNumberOfPeople()));
		txt->append(QString("\n"));
		//		if(l[i].getTitle().find(this->edit->toPlainText()) != std::string::npos))

	}

}

void a14::firstScene()
{
	first = new QWidget{};

	QVBoxLayout* hL = new QVBoxLayout{};
	QPushButton* admin = new QPushButton{ "&Admin" };
	QPushButton* user = new QPushButton{ "&User" };

	/*QLinearGradient buttonGradient(0, 0, 0, admin->height());
	buttonGradient.setColorAt(0, QColor(100, 120, 140));
	buttonGradient.setColorAt(1, QColor(160, 180, 200));


	QPalette palette = qApp->palette();
	palette.setBrush(QPalette::Base, buttonGradient);
	palette.setBrush(QPalette::Highlight, buttonGradient);
	palette.setBrush(QPalette::HighlightedText, Qt::white);
	palette.setBrush(QPalette::Text, Qt::white);

	admin->setPalette(palette);*/

	admin->setStyleSheet(QString("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 white, stop: 0.4 "
		"gray, stop:1 blue)"));
	user->setStyleSheet(QString("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 red, stop: 0.4 "
		"gray, stop:1 white)"));

	hL->addWidget(admin);
	hL->addWidget(user);

	first->setLayout(hL);

	connect(admin, &QPushButton::clicked, this, &a14::setAdmin);
	connect(user, &QPushButton::clicked, this, &a14::setUserButton);

	first->show();

	/*first->setFocusPolicy(Qt::NoFocus);
	admin->setFocusPolicy(Qt::NoFocus);
	user->setFocusPolicy(Qt::NoFocus);

	setFocusPolicy(Qt::StrongFocus);*/
}

void a14::setAdmin()
{
	this->first->hide();

	innit();
}

void a14::setUser()
{
	this->selectButton->hide();


	wnd = new QWidget{};
	vL = new QHBoxLayout{};
	wnd->setLayout(vL);


	QHBoxLayout* hL1 = new QHBoxLayout{};
	QWidget* actions1 = new QWidget{};

	QHBoxLayout* hL2 = new QHBoxLayout{};
	QWidget* actions2 = new QWidget{};

	userPrintList = new QTextEdit{};

	actions2->setLayout(hL2);
	hL2->addWidget(userPrintList);



	edit = new QTextEdit{};
	txt = new QTextEdit();
	txt->setFixedWidth(200);

	actions1->setLayout(hL1);
	txt->setReadOnly(true);
	hL1->addWidget(txt);
	hL1->addWidget(edit);

	edit->setFixedWidth(200);

	setList();


	updatePage = new QWidget{};



	QVBoxLayout* updateVl = new QVBoxLayout{};
	updatePage->setLayout(updateVl);


	updateTitleButton = new QPushButton{ "Add Event" };
	connect(updateTitleButton, &QPushButton::clicked, this, &a14::addUserToRepo);
	updateVl->addWidget(updateTitleButton);

	updateDescButton = new QPushButton{ "Skip Event" };
	connect(updateDescButton, &QPushButton::clicked, this, &a14::skipUser);
	updateVl->addWidget(updateDescButton);

	updateNrOfPeopleButton = new QPushButton{ "Exit" };
	connect(updateNrOfPeopleButton, &QPushButton::clicked, this, &a14::breakFromUser);
	updateVl->addWidget(updateNrOfPeopleButton);




	boxes = new QWidget{};

	fL = new QFormLayout{};
	//details->setLayout(fL);

	QVBoxLayout* hL = new QVBoxLayout{};
	QPushButton* add = new QPushButton{ "&Add" };
	QPushButton* remove = new QPushButton{ "&Remove" };
	QPushButton* open = new QPushButton{ "&Open File" };



	QPushButton* table = new QPushButton{ "&Table" };
	hL->addWidget(add);
	hL->addWidget(remove);
	hL->addWidget(open);
	hL->addWidget(table);
	boxes->setLayout(fL);



	labelName = new QLabel{ "&1. The month" };
	textBoxTitle = new QLineEdit{};
	labelName->setBuddy(textBoxTitle);
	fL->addRow(labelName, textBoxTitle);



	QWidget* actions = new QWidget{};
	actions->setLayout(hL);

	

	eventButton = new QPushButton{ "&Add the event" };
	fL->addWidget(eventButton);


	connect(add, &QPushButton::clicked, this, &a14::setUserAddEvent);
	connect(open, &QPushButton::clicked, this, &a14::openFiles);

	connect(remove, &QPushButton::clicked, this, &a14::setUpRemoveFromRepo);

	connect(table, &QPushButton::clicked, this, &a14::setUpTable);


	//vL->addWidget(txt);
	//vL->addWidget(edit);
	//vL->addWidget(boxes);


	vL->addWidget(actions1);
	vL->addWidget(actions);
	userPrintList->setFixedWidth(250);
	userPrintList->hide();
	vL->addWidget(actions2);

	//bindShortcut(undoButton, Qt::Key_Enter);

	//QObject::connect(new QShortcut(Qt::Key_A, undoButton), &QShortcut::activated, [undoButton]() { undoButton->animateClick(); });

	wnd->show();
	//wnd->setFocusPolicy(Qt::StrongFocus);
	
	/*actions1->setFocusPolicy(Qt::NoFocus);
	actions2->setFocusPolicy(Qt::NoFocus);
	actions->setFocusPolicy(Qt::NoFocus);
	eventButton->setFocusPolicy(Qt::NoFocus);
	add->setFocusPolicy(Qt::NoFocus);
	remove->setFocusPolicy(Qt::NoFocus);
	open->setFocusPolicy(Qt::NoFocus);
	table->setFocusPolicy(Qt::NoFocus);
	updateTitleButton->setFocusPolicy(Qt::NoFocus);
	updateDescButton->setFocusPolicy(Qt::NoFocus);
	updateNrOfPeopleButton->setFocusPolicy(Qt::NoFocus);


	wnd->setFocusPolicy(Qt::NoFocus);
	userPrintList->setFocusPolicy(Qt::NoFocus);
	txt->setFocusPolicy(Qt::NoFocus);
	edit->setFocusPolicy(Qt::NoFocus);*/
	//setFocusPolicy(Qt::StrongFocus);

}

void a14::addNewEvent()
{

	if (updatePage->isVisible())
	{
		updatePage->hide();
		vL->removeWidget(updatePage);
		fL->removeRow(fL->rowCount() - 1);
	}


	vL->addWidget(boxes);
	eventButton->setText("Add new event");
	eventButton->show();
	boxes->show();

	disconnect(eventButton, &QPushButton::clicked, this, &a14::removeEventFromRepo);
	connect(eventButton, &QPushButton::clicked, this, &a14::addEventToRepo);
}

void a14::addEventToRepo()
{
	setLineEdits();
	boxes->hide();
	vL->removeWidget(boxes);

	disconnect(eventButton, &QPushButton::clicked, this, &a14::addEventToRepo);

	if (dayQT == 0 || monthQT == 0 || yearQT == 0 || minutesQT == 0 || hourQT == 0 || nrOfPeopleQT == -1)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Wrong input data!");
		messageBox.setFixedSize(500, 200);
		return;
	}

	try
	{
		UI.serv.addEvent(titleQT, descQT, linkQT, nrOfPeopleQT, dayQT, monthQT, yearQT, hourQT, minutesQT);
		Date d{ dayQT, monthQT, yearQT, hourQT, minutesQT };
		Event tmp = Event{ titleQT, descQT, linkQT, nrOfPeopleQT, d};
		std::unique_ptr<Action> ptr1 = std::make_unique<ActionAdd>(tmp, UI.serv.repo);
		this->actions_undo.push_back(std::move(ptr1));

		this->actions_redo.clear();
		UI.serv.getData().writeToFile("out.txt");

	}
	catch (Exception& ex)
	{
		//std::cout << ex.what();

		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	setList();
}

void a14::updateEvent()
{


	if (!updatePage->isVisible())
	{

		labelNewField = new QLabel{ "&To Update: " };
		textBoxUpdateField = new QLineEdit{};
		labelNewField->setBuddy(textBoxUpdateField);
		fL->addRow(labelNewField, textBoxUpdateField);

		vL->addWidget(updatePage);
		vL->addWidget(boxes);
		updatePage->show();
		boxes->show();
		eventButton->hide();
	}

}

void a14::updateTitle()
{
	setLineEdits();

	std::string updateString = textBoxUpdateField->text().toStdString();
	textBoxUpdateField->clear();

	vL->removeWidget(boxes);
	boxes->hide();
	vL->removeWidget(updatePage);
	fL->removeRow(fL->rowCount() - 1);

	updatePage->hide();

	disconnect(updateTitleButton, &QPushButton::clicked, this, &a14::updateTitle);

	try
	{
		UI.serv.updateTitle(titleQT, dayQT, monthQT, yearQT, hourQT, minutesQT, updateString);

		Date d{ dayQT, monthQT, yearQT, hourQT, minutesQT };
		Event tmp = Event{ titleQT, descQT, linkQT, nrOfPeopleQT, d };
		std::unique_ptr<Action> ptr1 = std::make_unique<ActionUpdateTitle>(tmp, UI.serv.repo, updateString);
		this->actions_undo.push_back(std::move(ptr1));


		this->actions_redo.clear();
		UI.serv.getData().writeToFile("out.txt");
	}
	catch (Exception& ex)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	setList();

}

void a14::updateDesc()
{
	setLineEdits();

	std::string updateString = textBoxUpdateField->text().toStdString();
	textBoxUpdateField->clear();

	vL->removeWidget(boxes);
	boxes->hide();
	vL->removeWidget(updatePage);
	fL->removeRow(fL->rowCount() - 1);

	updatePage->hide();

	disconnect(updateDescButton, &QPushButton::clicked, this, &a14::updateDesc);

	try
	{
		UI.serv.updateDesc(titleQT, dayQT, monthQT, yearQT, hourQT, minutesQT, updateString);

		Date d{ dayQT, monthQT, yearQT, hourQT, minutesQT };
		Event tmp = Event{ titleQT, descQT, linkQT, nrOfPeopleQT, d };
		std::unique_ptr<Action> ptr1 = std::make_unique<ActionUpdateDesc>(tmp, UI.serv.repo, updateString);
		this->actions_undo.push_back(std::move(ptr1));


		this->actions_redo.clear();
		UI.serv.getData().writeToFile("out.txt");
	}
	catch (Exception& ex)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	setList();
}

void a14::updateNr()
{
	setLineEdits();

	int updateString = textBoxUpdateField->text().toInt();
	textBoxUpdateField->clear();

	vL->removeWidget(boxes);
	boxes->hide();
	vL->removeWidget(updatePage);
	fL->removeRow(fL->rowCount() - 1);

	updatePage->hide();

	disconnect(updateNrOfPeopleButton, &QPushButton::clicked, this, &a14::updateNr);

	try
	{
		UI.serv.updateNrOfPeople(titleQT, dayQT, monthQT, yearQT, hourQT, minutesQT, updateString);

		Date d{ dayQT, monthQT, yearQT, hourQT, minutesQT };
		Event tmp = Event{ titleQT, descQT, linkQT, nrOfPeopleQT, d };
		std::unique_ptr<Action> ptr1 = std::make_unique<ActionUpdateNr>(tmp, UI.serv.repo, updateString);
		this->actions_undo.push_back(std::move(ptr1));

		this->actions_redo.clear();
		UI.serv.getData().writeToFile("out.txt");
	}
	catch (Exception& ex)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	setList();
}

void a14::updateDate()
{
	setLineEdits();

	std::string updateString = textBoxUpdateField->text().toStdString();
	size_t start;
	size_t end = 0;
	std::vector<int> out;
	while ((start = updateString.find_first_not_of('/', end)) != std::string::npos)
	{
		end = updateString.find('/', start);
		out.push_back(stoi(updateString.substr(start, end - start)));
	}
	textBoxUpdateField->clear();

	vL->removeWidget(boxes);
	boxes->hide();
	vL->removeWidget(updatePage);
	fL->removeRow(fL->rowCount() - 1);

	updatePage->hide();


	disconnect(updateDateButton, &QPushButton::clicked, this, &a14::updateDate);

	try
	{
		UI.serv.updateDate(titleQT, dayQT, monthQT, yearQT, hourQT, minutesQT, out[0], out[1], out[2], out[3], out[4]);


		Date d{ dayQT, monthQT, yearQT, hourQT, minutesQT };
		Date uD{ out[0], out[1], out[2], out[3], out[4] };
		Event tmp = Event{ titleQT, descQT, linkQT, nrOfPeopleQT, d };
		std::unique_ptr<Action> ptr1 = std::make_unique<ActionUpdateDate>(tmp, UI.serv.repo, uD);

		this->actions_undo.push_back(std::move(ptr1));

		this->actions_redo.clear();
		UI.serv.getData().writeToFile("out.txt");
	}
	catch (Exception& ex)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	setList();
}

void a14::updateLink()
{
	setLineEdits();

	std::string updateString = textBoxUpdateField->text().toStdString();
	textBoxUpdateField->clear();

	vL->removeWidget(boxes);
	boxes->hide();
	vL->removeWidget(updatePage);
	fL->removeRow(fL->rowCount() - 1);

	updatePage->hide();

	disconnect(updateLinkButton, &QPushButton::clicked, this, &a14::updateLink);

	try
	{
		UI.serv.updateLink(titleQT, dayQT, monthQT, yearQT, hourQT, minutesQT, updateString);

		Date d{ dayQT, monthQT, yearQT, hourQT, minutesQT };
		Event tmp = Event{ titleQT, descQT, linkQT, nrOfPeopleQT, d };
		std::unique_ptr<Action> ptr1 = std::make_unique<ActionUpdateLink>(tmp, UI.serv.repo, updateString);
		this->actions_undo.push_back(std::move(ptr1));

		this->actions_redo.clear();
		UI.serv.getData().writeToFile("out.txt");
	}
	catch (Exception& ex)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	setList();

}

void a14::removeEvent()
{
	if (updatePage->isVisible())
	{
		updatePage->hide();
		vL->removeWidget(updatePage);
		fL->removeRow(fL->rowCount() - 1);
	}


	vL->addWidget(boxes);
	eventButton->setText("Remove");
	eventButton->show();
	boxes->show();


	disconnect(eventButton, &QPushButton::clicked, this, &a14::addEventToRepo);
	connect(eventButton, &QPushButton::clicked, this, &a14::removeEventFromRepo);
}

void a14::removeEventFromRepo()
{
	setLineEdits();
	boxes->hide();
	vL->removeWidget(boxes);

	disconnect(eventButton, &QPushButton::clicked, this, &a14::removeEventFromRepo);


	if (dayQT == 0 || monthQT == 0 || yearQT == 0 || minutesQT == 0 || hourQT == 0)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Wrong input data!");
		messageBox.setFixedSize(500, 200);
		return;
	}

	try
	{
		UI.serv.deleteEvent(titleQT, dayQT, monthQT, yearQT, hourQT, minutesQT);
		Date d{ dayQT, monthQT, yearQT, hourQT, minutesQT };
		Event tmp = Event{ titleQT, descQT, linkQT, nrOfPeopleQT, d };
		std::unique_ptr<Action> ptr1 = std::make_unique<ActionRemove>(tmp, UI.serv.repo);
		this->actions_undo.push_back(std::move(ptr1));

		this->actions_redo.clear();
		
		UI.serv.getData().writeToFile("out.txt");



	}
	catch (Exception& ex)
	{
		//std::cout << ex.what();

		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	setList();

}

void a14::setLineEdits()
{
	titleQT = textBoxTitle->text().toStdString();
	textBoxTitle->clear();
	descQT = textBoxDesc->text().toStdString();
	textBoxDesc->clear();
	linkQT = textBoxLink->text().toStdString();
	textBoxLink->clear();


	std::string s = textBoxNrOfPeople->text().toStdString();
	if (!(textBoxNrOfPeople->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		nrOfPeopleQT = -1;
	}
	else nrOfPeopleQT = textBoxNrOfPeople->text().toInt();
	textBoxNrOfPeople->clear();


	if (!(textBoxDay->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		dayQT = 0;
	}
	else dayQT = textBoxDay->text().toInt();
	textBoxDay->clear();


	if (!(textBoxMonth->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		monthQT = 0;
	}
	else monthQT = textBoxMonth->text().toInt();
	textBoxMonth->clear();

	if (!(textBoxYear->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		yearQT = 0;
	}
	else yearQT = textBoxYear->text().toInt();
	textBoxYear->clear();


	if (!(textBoxHour->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		hourQT = 0;
	}
	else hourQT = textBoxHour->text().toInt();
	textBoxHour->clear();

	if (!(textBoxMinute->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		minutesQT = 0;
	}
	else minutesQT = textBoxMinute->text().toInt();
	textBoxMinute->clear();
}

void a14::setList()
{
	std::vector<Event> list;

	EventVector tmp = UI.serv.getData();

	txt->clear();

	for (int i = 0; i < tmp.getEventLen(); i++)
	{
		list.push_back(Event{ tmp.getEvent(i).getTitle(), tmp.getEvent(i).getDescription(), tmp.getEvent(i).getLink(), tmp.getEvent(i).getNumberOfPeople(), tmp.getEvent(i).getDate() });
	}


	for (int i = 0; i < list.size(); i++) {
		txt->append(QString::number(i + 1));
		txt->append(QString(list[i].getTitle().c_str()));
		txt->append(QString(list[i].getDescription().c_str()));
		txt->append(QString(list[i].getLink().c_str()));
		txt->append(QString::number(list[i].getDate().getDay()));
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString("."));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(list[i].getDate().getMonth()));
		txt->moveCursor(QTextCursor::End);

		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString("."));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(list[i].getDate().getYear()));
		txt->moveCursor(QTextCursor::End);

		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString(" "));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(list[i].getDate().getHour()));
		txt->moveCursor(QTextCursor::End);

		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString(":"));
		txt->moveCursor(QTextCursor::End);
		txt->moveCursor(QTextCursor::End);
		txt->insertPlainText(QString::number(list[i].getDate().getMinute()));
		txt->moveCursor(QTextCursor::End);

		txt->append(QString::number(list[i].getNumberOfPeople()));
		txt->append(QString("\n"));
	}


}

void a14::setUserButton()
{
	selectButton = new QWidget{};

	QVBoxLayout* hL = new QVBoxLayout{};
	QPushButton* admin = new QPushButton{ "&CSV" };
	QPushButton* user = new QPushButton{ "&HTML" };

	hL->addWidget(admin);
	hL->addWidget(user);

	selectButton->setLayout(hL);

	connect(admin, &QPushButton::clicked, this, &a14::CSVsaveButton);
	connect(user, &QPushButton::clicked, this, &a14::HTMLsaveButton);


	first->hide();
	selectButton->show();

}

void a14::HTMLsaveButton()
{
	fileToUseQt = 2;
	setUser();
}

void a14::CSVsaveButton()
{
	fileToUseQt = 1;
	setUser();
}

void a14::setUserAddEvent()
{
	vL->addWidget(boxes);
	labelName->setText("The month:");
	eventButton->setText("OK");
	eventButton->show();
	boxes->show();

	disconnect(eventButton, &QPushButton::clicked, this, &a14::removeUserFromList);
	connect(eventButton, &QPushButton::clicked, this, &a14::addUserEvent);
}

void a14::addUserEvent()
{
	int m;
	vL->removeWidget(boxes);
	boxes->hide();
	if (!(textBoxTitle->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		m = 0;
	}
	else m = textBoxTitle->text().toInt();
	textBoxTitle->clear();


	//userPrintList->show();
	vL->addWidget(updatePage);
	updatePage->show();

	int startIndex, endIndex;
	UI.serv.getEvents(startIndex, endIndex, m);
	txt->clear();
	endIndexQT = endIndex;
	startIndexQT = startIndex;
	indexUserQT = startIndex;

	printUserTxt();



}

void a14::addUserToRepo()
{

	try
	{
		UI.serv.addUserEvent(indexUserQT, fileToUseQt);
	}
	catch (Exception& ex)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}

	edit->append(QString::number(indexUserQT + 1));
	edit->append(QString(UI.serv.getEvent(indexUserQT).getTitle().c_str()));
	edit->append(QString(UI.serv.getEvent(indexUserQT).getDescription().c_str()));
	edit->append(QString(UI.serv.getEvent(indexUserQT).getLink().c_str()));
	edit->append(QString::number(UI.serv.getEvent(indexUserQT).getDate().getDay()));
	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString("."));
	edit->moveCursor(QTextCursor::End);
	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getMonth()));
	edit->moveCursor(QTextCursor::End);

	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString("."));
	edit->moveCursor(QTextCursor::End);
	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getYear()));
	edit->moveCursor(QTextCursor::End);

	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString(" "));
	edit->moveCursor(QTextCursor::End);
	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getHour()));
	edit->moveCursor(QTextCursor::End);

	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString(":"));
	edit->moveCursor(QTextCursor::End);
	edit->moveCursor(QTextCursor::End);
	edit->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getMinute()));
	edit->moveCursor(QTextCursor::End);

	edit->append(QString::number(UI.serv.getEvent(indexUserQT).getNumberOfPeople()));
	edit->append(QString("\n"));

	if (indexUserQT == endIndexQT - 1)
		indexUserQT = startIndexQT - 1;
	indexUserQT++;
	printUserTxt();
}

void a14::skipUser()
{
	if (indexUserQT == endIndexQT - 1)
		indexUserQT = startIndexQT - 1;
	indexUserQT++;
	printUserTxt();
}

void a14::breakFromUser()
{
	vL->removeWidget(updatePage);
	updatePage->hide();
	txt->clear();

	if (fileToUseQt == 2)
	{
		UI.serv.getHTMLUser().writeToFile("outHTML.html");
	}
	else
		if (fileToUseQt == 1)
		{
			UI.serv.getCSVUser().writeToFile("outCSV.csv");
		}

}

void a14::printUserTxt()
{
	txt->clear();

	txt->append(QString::number(indexUserQT + 1));
	txt->append(QString(UI.serv.getEvent(indexUserQT).getTitle().c_str()));
	txt->append(QString(UI.serv.getEvent(indexUserQT).getDescription().c_str()));
	txt->append(QString(UI.serv.getEvent(indexUserQT).getLink().c_str()));
	txt->append(QString::number(UI.serv.getEvent(indexUserQT).getDate().getDay()));
	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString("."));
	txt->moveCursor(QTextCursor::End);
	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getMonth()));
	txt->moveCursor(QTextCursor::End);

	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString("."));
	txt->moveCursor(QTextCursor::End);
	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getYear()));
	txt->moveCursor(QTextCursor::End);

	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString(" "));
	txt->moveCursor(QTextCursor::End);
	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getHour()));
	txt->moveCursor(QTextCursor::End);

	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString(":"));
	txt->moveCursor(QTextCursor::End);
	txt->moveCursor(QTextCursor::End);
	txt->insertPlainText(QString::number(UI.serv.getEvent(indexUserQT).getDate().getMinute()));
	txt->moveCursor(QTextCursor::End);

	txt->append(QString::number(UI.serv.getEvent(indexUserQT).getNumberOfPeople()));
	txt->append(QString("\n"));



	system(std::string("start " + UI.serv.getEvent(indexUserQT).getLink()).c_str());
}

void a14::openFiles()
{
	if (fileToUseQt == 2)
	{
		UI.serv.getHTMLUser().openFile("outHTML.html");

	}
	else
		if (fileToUseQt == 1)
		{
			UI.serv.getCSVUser().openFile("outCSV.csv");
		}
}

void a14::setUpRemoveFromRepo()
{
	vL->addWidget(boxes);
	labelName->setText("Index:");
	textBoxTitle->clear();
	eventButton->setText("OK");
	eventButton->show();
	boxes->show();

	disconnect(eventButton, &QPushButton::clicked, this, &a14::addUserEvent);
	connect(eventButton, &QPushButton::clicked, this, &a14::removeUserFromList);
}

void a14::removeUserFromList()
{
	int m = 1;
	vL->removeWidget(boxes);
	boxes->hide();

	if (!(textBoxTitle->text().toStdString().find_first_not_of("0123456789") == std::string::npos))
	{
		m = 0;
	}
	else m = textBoxTitle->text().toInt();
	textBoxTitle->clear();
	try
	{
		UI.serv.deleteUserEvent(m, fileToUseQt);
	}
	catch (Exception& ex)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", ex.what().c_str());
		messageBox.setFixedSize(500, 200);
		return;
	}
	EventVector tmp;

	std::vector<Event> list;

	if (fileToUseQt == 2)
	{
		tmp = UI.serv.getHTMLUser();
	}
	else
		if (fileToUseQt == 1)
		{
			tmp = UI.serv.getCSVUser();
		}


	edit->clear();

	for (int i = 0; i < tmp.getEventLen(); i++)
	{
		list.push_back(Event{ tmp.getEvent(i).getTitle(), tmp.getEvent(i).getDescription(), tmp.getEvent(i).getLink(), tmp.getEvent(i).getNumberOfPeople(), tmp.getEvent(i).getDate() });
	}


	for (int i = 0; i < list.size(); i++) {
		edit->append(QString::number(i + 1));
		edit->append(QString(list[i].getTitle().c_str()));
		edit->append(QString(list[i].getDescription().c_str()));
		edit->append(QString(list[i].getLink().c_str()));
		edit->append(QString::number(list[i].getDate().getDay()));
		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString("."));
		edit->moveCursor(QTextCursor::End);
		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString::number(list[i].getDate().getMonth()));
		edit->moveCursor(QTextCursor::End);

		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString("."));
		edit->moveCursor(QTextCursor::End);
		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString::number(list[i].getDate().getYear()));
		edit->moveCursor(QTextCursor::End);

		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString(" "));
		edit->moveCursor(QTextCursor::End);
		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString::number(list[i].getDate().getHour()));
		edit->moveCursor(QTextCursor::End);

		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString(":"));
		edit->moveCursor(QTextCursor::End);
		edit->moveCursor(QTextCursor::End);
		edit->insertPlainText(QString::number(list[i].getDate().getMinute()));
		edit->moveCursor(QTextCursor::End);

		edit->append(QString::number(list[i].getNumberOfPeople()));
		edit->append(QString("\n"));
	}


	if (fileToUseQt == 2)
	{
		UI.serv.getHTMLUser().writeToFile("outHTML.html");
	}
	else
		if (fileToUseQt == 1)
		{
			UI.serv.getCSVUser().writeToFile("outCSV.csv");
		}

	disconnect(eventButton, &QPushButton::clicked, this, &a14::removeUserFromList);
}

void a14::performUndo()
{
	if (actions_undo.size() == 0)
		return;


	auto pt1 = std::move(this->actions_undo[this->actions_undo.size() - 1]);
	pt1->executeUndo();

	this->actions_redo.push_back(std::move(pt1));

	this->actions_undo.pop_back();

	setList();
}

void a14::performRedo()
{
	if (this->actions_redo.size() == 0)
		return;


	auto pt1 = std::move(this->actions_redo[this->actions_redo.size() - 1]);
	pt1->executeRedo();

	this->actions_undo.push_back(std::move(pt1));

	this->actions_redo.pop_back();

	setList();

}

void a14::setUpTable()
{
	QTableView* view = new QTableView;
	EventVector tmp;
	std::vector<Event> list;

	if (fileToUseQt == 2)
	{
		tmp = UI.serv.getHTMLUser();
	}
	else
		if (fileToUseQt == 1)
		{
			tmp = UI.serv.getCSVUser();
		}
	for (int i = 0; i < tmp.getEventLen(); i++)
	{
		list.push_back(Event{ tmp.getEvent(i).getTitle(), tmp.getEvent(i).getDescription(), tmp.getEvent(i).getLink(), tmp.getEvent(i).getNumberOfPeople(), tmp.getEvent(i).getDate() });
	}
	tableModel = new EventTable{ list };
	view->setModel(tableModel);
	view->show();
	
}

//void qt_a11::showTheBarChart()
//{
//	QBarSet* set0 = new QBarSet("Jane");
//	QBarSet* set1 = new QBarSet("John");
//	QBarSet* set2 = new QBarSet("Axel");
//	QBarSet* set3 = new QBarSet("Mary");
//	QBarSet* set4 = new QBarSet("Samantha");
//
//	*set0 << 1 << 2 << 3 << 4 << 5 << 6;
//	*set1 << 5 << 0 << 0 << 4 << 0 << 7;
//	*set2 << 3 << 5 << 8 << 13 << 8 << 5;
//	*set3 << 5 << 6 << 7 << 3 << 4 << 5;
//	*set4 << 9 << 7 << 5 << 3 << 1 << 2;
//
//
//	QBarSeries* series = new QBarSeries();
//	series->append(set0);
//	series->append(set1);
//	series->append(set2);
//	series->append(set3);
//	series->append(set4);
//
//	QChart* chart = new QChart();
//	chart->addSeries(series);
//	chart->setTitle("Simple barchart example");
//	chart->setAnimationOptions(QChart::SeriesAnimations);
//
//
//	QStringList categories;
//	categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
//	QBarCategoryAxis* axis = new QBarCategoryAxis();
//	axis->append(categories);
//	chart->createDefaultAxes();
//	chart->setAxisX(axis, series);
//
//	chart->legend()->setVisible(true);
//	chart->legend()->setAlignment(Qt::AlignBottom);
//
//	chartView = new QChartView(chart);
//	chartView->setRenderHint(QPainter::Antialiasing);
//
//}


void a14::keyPressEvent(QKeyEvent* e)
{
	//(e->modifiers() == Qt::CTRL) && 
	if (e->key() == Qt::Key_U)
	{
		emit performUndo();
		return;
	}
}


int main(int argc, char* argv[])
{



	QApplication a(argc, argv);
	a14 gui;
	gui.UI = ui{};


	gui.firstScene();


	return a.exec();

	return 0;
}