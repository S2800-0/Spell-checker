#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_set>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCheckSpelling(); // Slot for spell-check button

private:
    Ui::MainWindow *ui;

    std::vector<std::string> loadDictionary(const std::string &filename);
    std::unordered_set<std::string> createDictionaryHash(const std::vector<std::string> &dictionary);
    std::vector<std::string> generateEdits1(const std::string &word);
    std::vector<std::string> spellCheck(const std::string &word, const std::unordered_set<std::string> &dict_hash);

    std::unordered_set<std::string> dictHash; // Dictionary hash for quick lookups
};
#endif // MAINWINDOW_H
