#ifndef BWV_BMAINWINDOW_HH
#define BWV_BMAINWINDOW_HH

#include <QMainWindow>

class QWidget;

namespace awv 
{
    class BMainWindow : public QMainWindow
    {

        Q_OBJECT

        public:
            BMainWindow(QWidget* parent = nullptr);
            ~BMainWindow();

        public slots:
            void button_toggled(int id, bool state);

        private:
    };
}

#endif
