#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Connect digit buttons
    connect(ui->pushButton_0, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_1, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_2, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_3, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_4, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_5, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_6, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_7, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_8, &QPushButton::released, this, &Widget::digit_pressed);
    connect(ui->pushButton_9, &QPushButton::released, this, &Widget::digit_pressed);

    // Connect operator buttons
    connect(ui->pushButton_Plus, &QPushButton::released, this, &Widget::operator_pressed);
    connect(ui->pushButton_Minus, &QPushButton::released, this, &Widget::operator_pressed);
    connect(ui->pushButton_Multiply, &QPushButton::released, this, &Widget::operator_pressed);
    connect(ui->pushButton_Divide, &QPushButton::released, this, &Widget::operator_pressed);

    // Connect equals and clear buttons
    connect(ui->pushButton_Equals, &QPushButton::released, this, &Widget::equals_pressed);
    connect(ui->pushButton_Clear, &QPushButton::released, this, &Widget::clear_pressed);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::digit_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString button_value = button->text();
    QString display_value = ui->Display_Input->text();

    if (display_value == "0") {
        update_display(button_value);
    } else {
        update_display(display_value + button_value);
    }
}

void Widget::operator_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString new_operator = button->text();
    QString display_value = ui->Display_Input->text();
    double operand = display_value.split(' ').last().toDouble();

    values.push(operand);
    operators.push(new_operator);
    update_display(display_value + " " + new_operator + " ");
}

void Widget::equals_pressed()
{
    QString display_value = ui->Display_Input->text();
    double operand = display_value.split(' ').last().toDouble();
    values.push(operand);
    apply_all_pending_operators();

    double result = values.isEmpty() ? 0 : values.pop();
    ui->Display_Output->setText(QString::number(result));
    ui->Display_Input->clear(); // Clear display after calculation

    // Clear the stacks
    values.clear();
    operators.clear();
}

void Widget::clear_pressed()
{
    ui->Display_Input->clear();
    ui->Display_Output->clear();
    values.clear();
    operators.clear();
}

void Widget::apply_pending_operator(const QString& new_operator)
{
    while (!operators.isEmpty() && (operators.top() == "*" || operators.top() == "/")) {
        QString op = operators.pop();
        double right = values.pop();
        double left = values.pop();

        if (op == "*") {
            values.push(left * right);
        } else if (op == "/") {
            values.push(right != 0 ? left / right : 0); // Handle division by zero
        }
    }
    operators.push(new_operator);
}

void Widget::apply_all_pending_operators()
{
    while (!operators.isEmpty()) {
        QString op = operators.pop();
        double right = values.pop();
        double left = values.pop();

        if (op == "+") {
            values.push(left + right);
        } else if (op == "-") {
            values.push(left - right);
        } else if (op == "*") {
            values.push(left * right);
        } else if (op == "/") {
            values.push(right != 0 ? left / right : 0); // Handle division by zero
        }
    }
}

void Widget::update_display(const QString& text)
{
    ui->Display_Input->setText(text);
}
