#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void digit_pressed();
    void operator_pressed();
    void equals_pressed();
    void clear_pressed();

private:
    Ui::Widget *ui;
    QStack<double> values;
    QStack<QString> operators;

    void apply_pending_operator(const QString& new_operator);
    void apply_all_pending_operators();
    void update_display(const QString& text);
};

#endif // WIDGET_H
