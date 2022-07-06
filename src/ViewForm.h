#ifndef VIEWFORM_H
#define VIEWFORM_H

#include <QWidget>

namespace Ui
{
class ViewForm;
}

class ViewForm : public QWidget
{
    Q_OBJECT
signals:
    void moveSplitterView(QWidget*, int);
    void closeSplitterView(QWidget*);
public:
    explicit ViewForm(QWidget *parent = nullptr);
    ~ViewForm();

    void setViewWidget(QWidget * w);

    void updateIndex(int);
    QWidget * getView();
    void hideLayoutButtons();
private slots:
    void on_pushButton_Left_clicked();

    void on_pushButton_Right_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::ViewForm *ui;
    int _index;
    QWidget * _view;
};

#endif // VIEWFORM_H
