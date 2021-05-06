#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "card.h"
#include "timer.h"
#include "grid.h"
#include "scoreboard.h"
#include <QTime>
#include <QProcess>

// this is the main function which builds the application and runs it
int main(int argc, char *argv[])
{
    // create the necessary buttons, layouts etc. and do the connections
    QApplication app(argc, argv);
    QWidget *cw = new QWidget;
    QVBoxLayout *vb = new QVBoxLayout();
    QHBoxLayout *hb = new QHBoxLayout();
    QPushButton *ng = new QPushButton("New Game");
    QPushButton *q = new QPushButton("Quit");
    QObject::connect(q, SIGNAL(clicked()), &app, SLOT(quit()));
    Timer *t = new Timer();
    Scoreboard *s = new Scoreboard(t->timer);
    hb->addWidget(t->label);
    hb->addWidget(s->label);
    QSpacerItem *si = new QSpacerItem(10, 0,
                                      QSizePolicy::Expanding,
                                      QSizePolicy::Expanding);
    hb->addSpacerItem(si);
    hb->addWidget(ng);
    hb->addWidget(q);
    vb->addLayout(hb);

    // this 2-d array will hold which places are occupied in the grid
    bool grid[5][6] = {false};

    Grid *gl = new Grid();

    QObject::connect(ng, SIGNAL(clicked()), gl, SLOT(restart()));
    QObject::connect(t, SIGNAL(lost()), gl, SLOT(end_lost()));
    QObject::connect(gl, SIGNAL(gridmatch()), s, SLOT(increment()));

    // this segment of the code creates cards, assigns words to them in pairs
    // and assigns them a random place in the grid
    QString text;
    std::srand(time(0));
    for(int i=0; i<15; i++){
        switch (i) {
        case 0:
            text = "robot";
            break;
        case 1:
            text = "ball";
            break;
        case 2:
            text = "turtle";
            break;
        case 3:
            text = "diamond";
            break;
        case 4:
            text = "crystal";
            break;
        case 5:
            text = "doll";
            break;
        case 6:
            text = "snake";
            break;
        case 7:
            text = "crab";
            break;
        case 8:
            text = "cat";
            break;
        case 9:
            text = "dog";
            break;
        case 10:
            text = "book";
            break;
        case 11:
            text =  "sword";
            break;
        case 12:
            text = "shield";
            break;
        case 13:
            text = "spider";
            break;
        case 14:
            text = "candle";
            break;
        }
        for(int j = 0; j <2; j++) {
            Card *randButton = new Card(text, gl->curclicked);
            QObject::connect(randButton, SIGNAL(clicked()),
                             randButton, SLOT(reveal()));
            QObject::connect(randButton, SIGNAL(checknow()), gl, SLOT(check_match()));
            int row = std::rand() % 5;
            int col = std::rand() % 6;

            // if the randomly assigned place is already occupied
            // reroll for new coordinates until it's good
            while (grid[row][col]) {
                row = std::rand() % 5;
                col = std::rand() % 6;
            }
            gl->addWidget(randButton, row, col, 1, 1);
            grid[row][col] = true;
        }
}
    vb->addLayout(gl);
    QSpacerItem *si2 = new QSpacerItem(0, 10,
                                      QSizePolicy::Expanding,
                                      QSizePolicy::Expanding);
    vb->addSpacerItem(si2);


    cw->setWindowTitle("Card Matching Game");
    cw->resize(640, 480);
    cw->setLayout(vb);
    cw->show();

    return app.exec();
}
