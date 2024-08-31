#ifndef DEDELEGATE_H
#define DEDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QAbstractItemView>
#include <QDebug>

class DEDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public :
    DEDelegate(QObject *parent = 0): QStyledItemDelegate(parent){}
signals:
    void editingFinished();
    void comboxTextChanged(QString text);
public slots:
    void onEditingFinished()
    {
        emit editingFinished();
    }
    void onComboxCurTextChanged(QString text)
    {
        emit comboxTextChanged(text);
    }
};

class ReadOnlyDelegate: public DEDelegate
{
    Q_OBJECT
public :
    ReadOnlyDelegate(QObject *parent = 0): DEDelegate(parent){}
    QWidget *createEditor(QWidget*parent,  const QStyleOptionViewItem &option,
                          const QModelIndex &index)  const
    {
        return NULL;
    }
};

class IntDelegate: public DEDelegate
{
    Q_OBJECT
public :
    IntDelegate(QObject *parent = 0): DEDelegate(parent){}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(new QIntValidator(editor));
        connect(editor, &QLineEdit::editingFinished, this, &DEDelegate::onEditingFinished);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast <QLineEdit*>(editor);
        lineEdit->setText(text);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const  QModelIndex &index)  const
    {
        QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

class DoubleDelegate: public DEDelegate
{
    Q_OBJECT
public :
    DoubleDelegate(QObject *parent = 0): DEDelegate(parent){}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(new QDoubleValidator(editor));
        connect(editor, &QLineEdit::editingFinished, this, &DEDelegate::onEditingFinished);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast <QLineEdit*>(editor);
        lineEdit->setText(text);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const  QModelIndex &index)  const
    {
        QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

class BoolDelegate : public DEDelegate
{
    Q_OBJECT
public :
    BoolDelegate(QObject *parent = 0): DEDelegate(parent){}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItem( "True" );
        editor->addItem( "False" );
        connect(editor, &QComboBox::currentTextChanged, this, &DEDelegate::onComboxCurTextChanged);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox =  static_cast <QComboBox*>(editor);
        int tindex = comboBox->findText(text);
        comboBox->setCurrentIndex(tindex);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const
    {
        QComboBox *comboBox =  static_cast<QComboBox*>(editor);
        QString text = comboBox->currentText();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const  QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

class ComboxDelegate : public DEDelegate
{
    Q_OBJECT
public :
    ComboxDelegate(QList<QString> members, QObject *parent = 0): DEDelegate(parent)
    {
        m_members = members;
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        QComboBox *editor = new QComboBox(parent);
        for(auto &str: m_members)
        {
            editor->addItem(str);
        }
        connect(editor, &QComboBox::currentTextChanged, this, &DEDelegate::onComboxCurTextChanged);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox =  static_cast <QComboBox*>(editor);
        int tindex = comboBox->findText(text);
        comboBox->setCurrentIndex(tindex);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const
    {
        QComboBox *comboBox =  static_cast<QComboBox*>(editor);
        QString text = comboBox->currentText();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const  QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
private:
    QList<QString> m_members;
};

#endif // DEDELEGATE_H
