#ifndef AWV_TYPEDIALOG_HH
#define AWV_TYPEDIALOG_HH

#include <string>

#include <QDialog>

class QWidget;
class QListWidgetItem;

namespace awv
{
    class TypeDialog : public QDialog
    {

        Q_OBJECT

        public:
            TypeDialog(QWidget* parent = nullptr);
            ~TypeDialog();

            std::string model_type();

        private slots:
            void       type_selected(QListWidgetItem*);

        private:
            std::string      model_type_;
    };
}
#endif
