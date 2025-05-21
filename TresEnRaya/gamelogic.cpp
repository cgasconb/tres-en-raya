#include "gamelogic.h"

GameLogic::GameLogic(QObject *parent)
    : QObject(parent), m_board(9, ""), m_currentPlayer("X"), m_gameOver(false), m_winner(""), m_vsAI(false)
{}

QString GameLogic::currentPlayer() const {
    return m_currentPlayer;
}

bool GameLogic::gameOver() const {
    return m_gameOver;
}

QString GameLogic::winner() const {
    return m_winner;
}

QString GameLogic::markAt(int index) const {
    return m_board.value(index);
}

void GameLogic::playAt(int index) {
    if (m_gameOver || m_board[index] != "")
        return;

    m_board[index] = m_currentPlayer;
    emit markChanged(index);

    checkWinner();

    if (!m_gameOver) {
        m_currentPlayer = (m_currentPlayer == "X") ? "O" : "X";
        emit currentPlayerChanged();

        if (m_vsAI && m_currentPlayer == "O") {
            QTimer::singleShot(300, this, SLOT(makeAIMove()));
        }
    }
}

void GameLogic::checkWinner() {
    const int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto& w : wins) {
        if (!m_board[w[0]].isEmpty() &&
            m_board[w[0]] == m_board[w[1]] &&
            m_board[w[1]] == m_board[w[2]]) {
            m_gameOver = true;
            m_winner = m_board[w[0]];
            emit gameOverChanged();
            return;
        }
    }

    if (!m_board.contains("")) {
        m_gameOver = true;
        m_winner = "Empate";
        emit gameOverChanged();
    }
}


int GameLogic::checkAlmostWinner() {
    const int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    // Check if AI is close to win
    for (auto& w : wins) {
        if (m_board[w[0]] == "O" &&
            m_board[w[2]].isEmpty() &&
            m_board[w[0]] == m_board[w[1]]) {
            return w[2];
        }

        if (m_board[w[0]] == "O" &&
            m_board[w[1]].isEmpty() &&
            m_board[w[0]] == m_board[w[2]]) {
            return w[1];
        }

        if (m_board[w[2]] == "O" &&
            m_board[w[0]].isEmpty() &&
            m_board[w[2]] == m_board[w[1]]) {
            return w[0];
        }
    }

    // Check if User is close to win
    for (auto& w : wins) {
        if (m_board[w[0]] == "X" &&
            m_board[w[2]].isEmpty() &&
            m_board[w[0]] == m_board[w[1]]) {
            return w[2];
        }

        if (m_board[w[0]] == "X" &&
            m_board[w[1]].isEmpty() &&
            m_board[w[0]] == m_board[w[2]]) {
            return w[1];
        }

        if (m_board[w[2]] == "X" &&
            m_board[w[0]].isEmpty() &&
            m_board[w[2]] == m_board[w[1]]) {
            return w[0];
        }
    }

    return -1;
}


void GameLogic::reset() {
    m_board.fill("");
    m_currentPlayer = "X";
    m_gameOver = false;
    m_winner = "";
    emit boardChanged();
    emit currentPlayerChanged();
    emit gameOverChanged();
}


bool GameLogic::vsAI() const {
    return m_vsAI;
}

void GameLogic::setVsAI(bool value) {
    if (m_vsAI != value) {
        m_vsAI = value;
        emit vsAIChanged();
    }
}

void GameLogic::makeAIMove() {
    if (!m_vsAI || m_gameOver || m_currentPlayer != "O")
        return;

    int critic_option = checkAlmostWinner();

    if(critic_option < 0){
        QList<int> empty;
        for (int i = 0; i < m_board.size(); ++i)
            if (m_board[i].isEmpty())
                empty << i;

        if (!empty.isEmpty()) {
            int choice = empty.at(QRandomGenerator::global()->bounded(empty.size()));
            playAt(choice);
        }
    }else{
        playAt(critic_option);
    }

}
