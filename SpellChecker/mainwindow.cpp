#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load dictionary when the application starts
    std::vector<std::string> dictionary = loadDictionary(":/resources/words.txt"); // Assume words.txt is a resource file
    dictHash = createDictionaryHash(dictionary);

    // Connect the button to the slot
    connect(ui->checkButton, &QPushButton::clicked, this, &MainWindow::onCheckSpelling);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<std::string> MainWindow::loadDictionary(const std::string &filename)
{
    std::vector<std::string> dictionary;
    QFile file(QString::fromStdString(filename));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Could not open dictionary file!");
        return dictionary;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        dictionary.push_back(in.readLine().toStdString());
    }

    return dictionary;
}

std::unordered_set<std::string> MainWindow::createDictionaryHash(const std::vector<std::string> &dictionary)
{
    return std::unordered_set<std::string>(dictionary.begin(), dictionary.end());
}

std::vector<std::string> MainWindow::generateEdits1(const std::string &word)
{
    std::vector<std::string> edits;
    int n = word.length();

    // Deletions
    for (int i = 0; i < n; ++i)
    {
        edits.push_back(word.substr(0, i) + word.substr(i + 1));
    }

    // Insertions
    for (int i = 0; i <= n; ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            edits.push_back(word.substr(0, i) + c + word.substr(i));
        }
    }

    // Substitutions
    for (int i = 0; i < n; ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (c != word[i])
            {
                edits.push_back(word.substr(0, i) + c + word.substr(i + 1));
            }
        }
    }

    return edits;
}

std::vector<std::string> MainWindow::spellCheck(const std::string &word, const std::unordered_set<std::string> &dict_hash)
{
    std::vector<std::string> suggestions;
    std::vector<std::string> edits = generateEdits1(word);

    for (const std::string &edit : edits)
    {
        if (dict_hash.find(edit) != dict_hash.end())
        {
            suggestions.push_back(edit);
        }
    }

    return suggestions;
}

void MainWindow::onCheckSpelling()
{
    QString input = ui->textInput->toPlainText().trimmed();

    if (input.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please enter a word to check.");
        return;
    }

    std::string word = input.toStdString();

    ui->suggestionList->clear();

    if (dictHash.find(word) != dictHash.end())
    {
        ui->suggestionList->addItem(QString::fromStdString(word) + " is spelled correctly.");
    }
    else
    {
        std::vector<std::string> suggestions = spellCheck(word, dictHash);

        if (suggestions.empty())
        {
            ui->suggestionList->addItem("No suggestions found.");
        }
        else
        {
            for (const std::string &suggestion : suggestions)
            {
                ui->suggestionList->addItem(QString::fromStdString(suggestion));
            }
        }
    }
}
