#ifndef AWV_PARMDIALOG_HH
#define AWV_PARMDIALOG_HH

#include<string>
#include <QDialog>
#include <QLineEdit>

class QWidget;
class QLineEdit;
class QFileDialog;
class QGroupBox;

namespace awv
{
    class TypeDialog;
    class ParmStore;

    class ParmDialog : public QDialog
    {

        Q_OBJECT

        public:
            ParmDialog(const std::string& model_name, QWidget* parent = 0);
            ~ParmDialog();
            void refresh();
        private slots:
            void type_pressed();
            void dir_pressed();
            void nt_entered();
            void nx_entered();
            void nz_entered();
            void dt_entered();
            void dh_entered();

            void type_accepted();
            void dir_accepted();

            void accepted();
            void canceled();

        private:

            ParmStore*      parm_store_;
            QGroupBox*      parm_group_;
            TypeDialog*     type_dialog_;
            QFileDialog*    file_dialog_;
            std::string     model_type_;
            std::string     model_dir_;
            QLineEdit*      name_e_;
            QLineEdit*      type_e_;
            QLineEdit*      dir_e_;
            QLineEdit*      nt_e_;
            QLineEdit*      dt_e_;
            QLineEdit*      nx_e_;
            QLineEdit*      dh_e_;
            QLineEdit*      nz_e_;
    };

}

#endif
