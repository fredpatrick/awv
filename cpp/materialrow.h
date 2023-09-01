#ifndef AWV_MATERIALROW_HH
#define AWV_MATERIALROW_HH

#include <QObject>

class QGroupBox;
class QGridLayout;
class QLineEdit;
class QWidget;

namespace awv
{
    class MaterialRow : public QObject
    {
        Q_OBJECT

        class MaterialStore;

        public:
            MaterialRow(QGroupBox*   parent,
                        QGridLayout* layout,
                        int          irow,
                        int          index   = 0,
                        float        density = 0,
                        float        modulus = 0);
            ~MaterialRow();

            void         save(MaterialStore* mat_store);
            void         edit();

        public slots:
            void         index_entered();
            void         density_entered();
            void         modulus_entered();
        private:
            int          index_;
            float        density_;
            float        modulus_;
            float        velocity_;
            QLineEdit*   index_e_;
            QLineEdit*   density_e_;
            QLineEdit*   modulus_e_;
            QLineEdit*   velocity_e_;

            int          irow_;
            QGridLayout* mat_layout_;
    };
}
#endif
