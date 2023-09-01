#ifndef AWV_CMAINWINDOW_HH
#define AWV_CMAINWINDOW_HH

#include <QMainWindow>

class QWidget;

namespace awv 
{
    class CMainWindow : public QMainWindow
    {

        Q_OBJECT

        public:
            CMainWindow(QWidget* parent = nullptr);
            ~CMainWindow();

        public slots:
            void text_entered();
            void pushme_pressed();

        private:
    };
}

#endif
