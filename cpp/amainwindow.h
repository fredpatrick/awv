#ifndef AWV_AMAINWINDOW_HH
#define AWV_AMAINWINDOW_HH

#include <string>

#include <QMainWindow>


class Qwidget;
class QAction;
class QGroupBox;

namespace awv 
{
    class NameDialog;
    class ParmDialog;
    class ParmStore;
    class MaterialDialog;
    class MaterialStore;

    class AMainWindow : public QMainWindow
    {

        Q_OBJECT

        public:
            AMainWindow(QWidget* parent = nullptr);
            ~AMainWindow();

        public slots:
            void get_modelname();
            void name_accepted();
            void edit_parameters();
            void parm_accepted();
            void parm_rejected();
            void edit_materials();
            void material_accepted();
            void material_rejected();
            void exit();

        private:
            std::string      model_name_;
            QGroupBox*       central_widget_;
            NameDialog*      name_dialog_;
            ParmDialog*      parm_dialog_;
            ParmStore*       parm_store_;
            MaterialDialog*  material_dialog_;
            MaterialStore*   material_store_;
            QAction*         print_action_;
            QAction*         exit_action_;
            QAction*         name_action_;
            QAction*         edit_action_;
            QAction*         material_action_;
    };
}

#endif
