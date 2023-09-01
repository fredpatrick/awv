#ifndef AWV_MATERIALDIALOG_HH
#define AWV_MATERIALDIALOG_HH

#include <map>
#include <string>

#include <QDialog>

class QWidget;
class QScrollArea;
class QScrollBar;
class QGroupBox;
class QGridLayout;
class QVBoxLayout;
class QButtonGroup;
class QCheckBox;
class QLineEdit;

namespace awv
{
    class MaterialStore;

    class MaterialDialog : public QDialog
    {
        Q_OBJECT

        public:
            MaterialDialog(const std::string& model_name, QWidget* parent = 0);
            ~MaterialDialog();

            void         load_from_material_store();
            void         init_property_row(int irow, float density, float modulus);

        private slots:
            void         index_entered();
            void         density_entered();
            void         modulus_entered();
            void         edit_mode(int id, bool checked);
            void         add_row();
            void         edit_pressed();
            void         save_row(int index);
            void         remove_pressed();
            void         accepted();
            void         canceled();
            void         slider_moved(int value);
            void         value_changed(int value);

        private:
            MaterialStore*                 material_store_;
            std::map<int, int >            row_map_;

            QScrollArea*                   scroll_area_;
            QScrollBar*                    scroll_bar_;
            QGroupBox*                     scroll_group_;
            QVBoxLayout*                   scroll_layout_;
            QGroupBox*                     material_group_;
            QGridLayout*                   material_layout_;
            QButtonGroup*                  button_group_;
            int                            edit_row_;;
            int                            index_;
            float                          density_;
            float                          modulus_;
            float                          velocity_;
            QCheckBox*                     row0_cb_;
            QCheckBox*                     index_cb_;
            QLineEdit*                     index_e_;
            QLineEdit*                     density_e_;
            QLineEdit*                     modulus_e_;
            QLineEdit*                     velocity_e_;
    };

}

#endif
