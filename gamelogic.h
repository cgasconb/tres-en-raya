#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QStringList>
#include <QRandomGenerator>
#include <QTimer>

class GameLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentPlayer READ currentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged)
    Q_PROPERTY(QString winner READ winner NOTIFY gameOverChanged)
    Q_PROPERTY(bool vsAI READ vsAI WRITE setVsAI NOTIFY vsAIChanged)

public:
    explicit GameLogic(QObject *parent = nullptr);

    Q_INVOKABLE void reset();
    Q_INVOKABLE QString markAt(int index) const;
    Q_INVOKABLE void playAt(int index);
    QString currentPlayer() const;
    bool gameOver() const;
    QString winner() const;

    bool vsAI() const;
    void setVsAI(bool value);
    Q_INVOKABLE void makeAIMove();

signals:
    void boardChanged();
    void currentPlayerChanged();
    void gameOverChanged();
    void markChanged(int index);
    void vsAIChanged();

private:
    QStringList m_board;
    QString m_currentPlayer;
    QString m_winner;
    bool m_gameOver;
    bool m_vsAI;

    void checkWinner();
    int checkAlmostWinner();
};

#endif // GAMELOGIC_H
