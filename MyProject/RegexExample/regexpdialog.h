#ifndef REGEXPDIALOG_H
#define REGEXPDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

class RegExpDialog : public QDialog
{
    Q_OBJECT

public:
    RegExpDialog(QWidget *parent = nullptr);
    ~RegExpDialog();

private slots:
    void refresh();

private:
    QLabel *patternLabel;
    QLabel *escapedPatternLabel;
    QLabel *syntaxLabel;
    QLabel *textLabel;
    QComboBox *patternComboBox;
    QLineEdit *escapedPatternLineEdit;
    QComboBox *textComboBox;
    QComboBox *syntaxComboBox;
    QCheckBox *minimalCheckBox;
    QCheckBox *caseSensitiveCheckBox;

    QLabel *indexLabel;
    QLabel *matchedLengthLabel;
    QLineEdit *indexEdit;
    QLineEdit *matchedLengthEdit;

    enum { MaxCaptures = 6 };
    QLabel *captureLabels[MaxCaptures];
    QLineEdit *captureEdits[MaxCaptures];
};
#endif // REGEXPDIALOG_H
