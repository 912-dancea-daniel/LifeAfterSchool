#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a14.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QTextEdit>
#include <qdebug.h>
#include "domain.h"
#include "ui.h"
#include "ui.h"


#include <QtCharts/qbarset.h>
#include <QtCharts/qbarseries.h>

#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
#include <memory.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <qkeysequence.h>
#include <QShortcut>
#include "myTable.h"
#include <QTableView>
#include <QKeyEvent>

class a14 : public QMainWindow
{
    Q_OBJECT

public:
    a14(QWidget *parent = Q_NULLPTR);


    QTextEdit* edit;

    void innit();

    void changeCaption();

    void firstScene();

    void setAdmin();
    void setUser();

    void addNewEvent();
    void addEventToRepo();

    void updateEvent();
    void updateTitle();
    void updateDesc();
    void updateNr();
    void updateDate();
    void updateLink();

    void removeEvent();
    void removeEventFromRepo();

    void setLineEdits();

    void setList();

    void setUserButton();
    void HTMLsaveButton();
    void CSVsaveButton();

    void setUserAddEvent();
    void addUserEvent();

    void addUserToRepo();
    void skipUser();
    void breakFromUser();
    void printUserTxt();

    void openFiles();

    void setUpRemoveFromRepo();
    void removeUserFromList();

    void performUndo();
    void performRedo();
    //void showTheBarChart();

    bool isNumber(const std::string& str)
    {
        for (char const& c : str) {
            if (std::isdigit(c) == 0) return false;
        }
        return true;
    }

    void setUpTable();

    void keyPressEvent(QKeyEvent* e);


    ui UI;
    //QChartView* chartView;

private:
    Ui::a14Class ui1;

    std::vector<Event> l;
    EventTable* tableModel;

    QWidget* wnd;
    QHBoxLayout* vL;
    QTextEdit* txt;
    QWidget* boxes;
    QWidget* updatePage;
    QFormLayout* fL;
    QTextEdit* userPrintList;


    QWidget* first;
    QWidget* selectButton;
    QLabel* labelNewField;

    QLabel* labelName;
    QLineEdit* textBoxTitle;
    QLineEdit* textBoxDesc;
    QLineEdit* textBoxNrOfPeople;
    QLineEdit* textBoxLink;
    QLineEdit* textBoxDay;
    QLineEdit* textBoxMonth;
    QLineEdit* textBoxYear;
    QLineEdit* textBoxHour;
    QLineEdit* textBoxMinute;
    QLineEdit* textBoxUpdateField;

    QPushButton* eventButton;

    // QPushButton* showMyBarChart;
    QPushButton* updateTitleButton;
    QPushButton* updateDescButton;
    QPushButton* updateNrOfPeopleButton;
    QPushButton* updateLinkButton;
    QPushButton* updateDateButton;

    QPushButton* undoButton;
    QPushButton* redoButton;

    QShortcut* undoShortCut;




    int dayQT, monthQT, yearQT, hourQT, minutesQT, nrOfPeopleQT, indexUserQT, fileToUseQt = 1, endIndexQT, startIndexQT;
    std::vector<std::unique_ptr<Action>> actions_undo;
    std::vector<std::unique_ptr<Action>> actions_redo;

    std::string titleQT, linkQT, descQT;
};
