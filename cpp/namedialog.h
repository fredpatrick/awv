#ifndef AWV_NAMEDIALOG_HH
#define AWV_NAMEDIALOG_HH

#include <QDialog>

class QWidget;
class QListWidgetItem;
class QLabel;
class QLineEdit;
class QListWidget;

namespace awv
{


    class NameDialog : public QDialog
    {
        Q_OBJECT

        public:
            NameDialog(QWidget* parent = nullptr);
            ~NameDialog();

            std::string model_name();
        public slots:

        private slots:
            void name_entered();
            void name_selected(QListWidgetItem*);

        private:
            QLabel*      name_label_;
            QLineEdit*   name_edit_;
            QListWidget* name_list_;
            QLabel*      type_label_;
            QLineEdit*   type_edit_;
            QListWidget* type_list_;

            std::string  model_name_;
    };
            
}
#endif

