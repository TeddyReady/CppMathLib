#include "transpositiongroup.h"

TranspositionGroup::TranspositionGroup() {}

TranspositionGroup::TranspositionGroup(std::vector<std::pair<int, int>> data)
{
    std::sort(data.begin(), data.end());
    std::vector<int> multi, single;
    for (size_t i = 0; i < data.size(); i++) {
        bool access = true;
        if (data[i].first != data[i].second) {
            for (size_t K = 0; K < tp.size(); K++) {
                for (size_t k = 0; k < tp[K].size(); k++) {
                    if (tp[K][k] == data[i].second) {
                        access = false;
                        break;
                    }
                }
                if (!access) break;
            }
            if (access) {
                multi.push_back(data[i].second);
                for (int j = data[i].second;;) {
                    multi.push_back(data[j - 1].second);
                    if (data[j - 1].second == data[i].first) {
                        break;
                    } else {
                        j = data[j - 1].second;
                    }
                }
                tp.push_back(multi);
                multi.clear();
            }
        } else {
            single.push_back(data[i].second);
            tp.push_back(single);
            single.clear();
        }
    }
}

TranspositionGroup::TranspositionGroup(const QString &str, int order)
{
    //Syntax check
    QString base = str;
    int count_1 = 0, count_2 = 0;
    for (int i = 0; i < base.size(); i++) {
        if (base[i] == '(') count_1++;
        else if (base[i] == ')') count_2++;
    } bool error = false;
    if (count_1 == count_2) {
        for (int i = 0; i < base.size(); i++) {
            if (base[i] == ',' && base[i + 1] == ')') {
                error = true;
                break;
            }
        }
    } else error = true;
    if (!error) {
        //General add elements
        for (int i = 0; i < base.size(); i++) {
            if (base[i] == '(') {
                QVector<int> tmp; QString num; i++;
                while(base[i] != ')') {
                    num += base[i];
                    if (base[i + 1] == ',') {
                        tmp.push_back(QString(num).toInt());
                        num = "";
                        i += 2;
                    } else i++;
                }
                if (QString(num).toInt() <= order)
                    tmp.push_back(QString(num).toInt());
                else {error = true; break;}
                tp.push_back(tmp);
            }
        }
    } if (error) {
        tp.clear();
        for (int i = 1; i <= order; i++) {
            QVector<int> tmp; tmp.push_back(i);
            tp.push_back(tmp);
        } return;
    }
    //Add alone elements
    bool isFind = false;
    QVector<QVector<int>> local;
    for (int i = 1; i <= order; i++) {

        for (int J = 0; J < tp.size(); J++) {
            for (int j = 0; j < tp[J].size(); j++) {

                if (i == tp[J][j]) {
                    isFind = true;
                    break;
                }

            } if (isFind) break;
        }
        if (isFind) isFind = false;
        else {
            QVector<int> tmp;
            tmp.push_back(i);
            local.push_back(tmp);
        }

    } for (int i = 0; i < local.size(); i++) {
        tp.push_back(local[i]);
    }
}

TranspositionGroup::TranspositionGroup(QVector<int> data, int order)
{
    bool isFind = false;
    for (int i = 1; i <= order; i++) {
        for (int j = 0; j < data.size(); j++) {
            if (i == data[j]) isFind = true;
        } if (!isFind) {
            QVector<int> tmp;
            tmp.push_back(i);
            tp.push_back(tmp);
        } else isFind = false;
    } tp.push_back(data);
}

TranspositionGroup TranspositionGroup::operator *(TranspositionGroup &trans)
{
    QVector<std::pair<int, int>> result;
    for (int I = 0; I < tp.size(); I++) {
        for (int i = 0; i < tp[I].size(); i++) {
            for (int J = 0; J < trans.getTransposition().size(); J++) {
                for (int j = 0; j < trans.getTransposition()[J].size(); j++) {

                    if (tp[I].size() > 1) {
                        if (trans.getTransposition()[J].size() > 1) {
                            if (i + 1 != tp[I].size()) {
                                if (tp[I][i + 1] == trans.getTransposition()[J][j]) {
                                    if (j + 1 != trans.getTransposition()[J].size()) {
                                        result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][j + 1]));
                                    } else {
                                        result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][0]));
                                    }
                                }
                            } else {
                                if (tp[I][0] == trans.getTransposition()[J][j]) {
                                    if (j + 1 != trans.getTransposition()[J].size()) {
                                        result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][j + 1]));
                                    } else {
                                        result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][0]));
                                    }
                                }
                            }
                        } else {
                            if (i + 1 != tp[I].size()) {
                                if (tp[I][i + 1] == trans.getTransposition()[J][j])
                                    result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][j]));
                            } else {
                                if (tp[I][0] == trans.getTransposition()[J][j])
                                    result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][j]));
                            }
                        }
                    } else {
                        if (trans.getTransposition()[J].size() > 1) {
                            if (tp[I][i] == trans.getTransposition()[J][j]) {
                                if (j + 1 != trans.getTransposition()[J].size()) {
                                    result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][j + 1]));
                                } else {
                                    result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][0]));
                                }
                            }
                        } else {
                            if (tp[I][i] == trans.getTransposition()[J][j])
                                result.push_back(std::make_pair(tp[I][i], trans.getTransposition()[J][j]));
                        }
                    }

                }
            }
        }
    }
    TranspositionGroup tmp(result);
    return tmp;
}

TranspositionGroup TranspositionGroup::operator ~(){
    QVector<std::pair<int, int>> result;
    for (int I = 0; I < tp.size(); I++) {
        for (int i = 0; i < tp[I].size(); i++) {
            if (tp[I].size() > 1) {
                if (i + 1 != tp[I].size())
                    result.push_back(std::make_pair(tp[I][i], tp[I][i + 1]));
                else result.push_back(std::make_pair(tp[I][i], tp[I][0]));
            } else {
                result.push_back(std::make_pair(tp[I][i], tp[I][i]));
            }
        }
    }
    for (int i = 0; i < result.size(); i++) {
        std::swap(result[i].first, result[i].second);
    }
    TranspositionGroup tmp(result);
    return tmp;
}

bool TranspositionGroup::operator ==(const TranspositionGroup& trans){
    bool isFind = false;
    for (int I = 0; I < trans.tp.size(); I++) {

            for (int i = 0; i < trans.tp[I].size(); i++) {

                for (int J = 0; J < tp.size(); J++) {

                        for (int j = 0; j < tp[J].size(); j++) {

                            if (trans.tp[I][i] == tp[J][j]) {
                                if (trans.tp[I].size() == tp[J].size()) {
                                    if (trans.tp[I][(i + 1) % trans.tp[I].size()] == tp[J][(j + 1) % tp[J].size()]) {
                                        isFind = true;
                                        break;
                                    }
                                    else return false;
                                } else return false;
                            }

                        }
                        if (isFind) {
                            isFind = false;
                            break;
                        }

                }

            }

    } return true;
}

QString TranspositionGroup::writeToMode(ViewMode mode, bool forTest){
    QString result;
    switch (mode) {
    case ViewMode::Cycle: {
        bool isTrivial = true;
        for (int i = 0; i < tp.size(); i++) {
            if (tp[i].size() > 1) {
                isTrivial = false;
                break;
            }
        } if (!isTrivial) {
            for (int i = 0; i < tp.size(); i++) {
                for (int j = 0; j < tp[i].size(); j++){
                    if (tp[i].size() > 1) {
                        if (j == 0) result += "(" + QString::number(tp[i][j]) + ",";
                        else if (j == tp[i].size() - 1)
                            result += QString::number(tp[i][j]) + ")";
                        else
                            result += QString::number(tp[i][j]) + ",";
                    }
                }
            }
        } else {
            for (int i = 0; i < tp.size(); i++) {
                result += "(" + QString::number(tp[i][0]) + ")";
            }
        } break;
    }
    case ViewMode::Decomposition:
        for(int I = 0; I < tp.size(); I++) {
            if (tp[I].size() > 1) {
                for (int i = 0; i < tp[I].size() - 1; i++) {
                    result += "(" + QString::number(tp[I][0]) + "," + QString::number(tp[I][i + 1]) + ")";
                }
            }
        } break;
    case ViewMode::Neighbors: {
        TranspositionGroup *tmp = new TranspositionGroup(this->writeToMode(ViewMode::Decomposition), this->getTask());
        for (int i = 0; i < tmp->tp.size(); i++) {
            if (tmp->tp[i].size() > 1) {
                std::sort(tmp->tp[i].begin(), tmp->tp[i].end());
                if (tmp->tp[i][1] - tmp->tp[i][0] != 1) {
                    int target = tmp->tp[i][1];
                    tmp->tp[i][1] = tmp->tp[i][0] + 1;
                    QVector<QString> *options = new QVector<QString>;
                    options->push_back("(" + QString::number(tmp->tp[i][0]) + "," + QString::number(tmp->tp[i][1]) + ")");
                    while (tmp->tp[i][1] != target) {
                        options->push_back("(" + QString::number(tmp->tp[i][1]) + "," + QString::number(tmp->tp[i][1] + 1) + ")");
                        options->push_front("(" + QString::number(tmp->tp[i][1]) + "," + QString::number(tmp->tp[i][1] + 1) + ")");
                        tmp->tp[i][1]++;
                    } for (int j = 0; j < options->size(); j++) {
                        result += (*options)[j];
                    } delete options;
                } else result += "(" + QString::number(tmp->tp[i][0]) + "," + QString::number(tmp->tp[i][1]) + ")";
            }
        }
        delete tmp;
        break;
    }
    case ViewMode::Standart: {
        int cnt = 0;
        for (int i = 0; i < tp.size(); i++) {
            cnt += tp[i].size();
        }
        QVector<int> tmp; tmp.resize(cnt);
        for (int i = 0; i < tp.size(); i++) {
            for (int j = 0; j < tp[i].size(); j++){
                if (tp[i].size() > 1) {
                    if (j != tp[i].size() - 1) {
                       tmp[tp[i][j] - 1] = tp[i][j + 1];
                    } else {
                        tmp[tp[i][j] - 1] = tp[i][0];
                    }
                } else {
                    tmp[tp[i][j] - 1] = tp[i][j];
                }
            }
        } if (!forTest) {
            result += "\\left(\\begin{smallmatrix}";
            for (int i = 0; i < tmp.size(); i++) {
                result += QString::number(i + 1);
                if (i + 1 != tmp.size()) result += "&";
                else result += "\\\\";
            }
            for (int i = 0; i < tmp.size(); i++) {
                if (i != tmp.size() - 1)
                    result += QString::number(tmp[i]) + " & ";
                else result += QString::number(tmp[i]) + "\\end{smallmatrix}\\right)";
            }
        } else {
            result += "(";
            for (int i = 0; i < tmp.size(); i++) {
                if (i != tmp.size() - 1)
                    result += QString::number(tmp[i]) + ",";
                else result += QString::number(tmp[i]) + ")";
            }
        } break;
    }} return result;
}

int TranspositionGroup::getTask()
{
    int cnt = 0;
    for (size_t i = 0; i < tp.size(); i++)
    {
        cnt += tp[i].size();
    }
    return cnt;
}

std::vector<std::vector<int>>& TranspositionGroup::getTransposition()
{
    return tp;
}

ViewMode TranspositionGroup::getViewMode()
{
    return mode;
}

QString TranspositionGroup::cycleType(){
    int maxCycle = 0;
    for (int i = 0; i < tp.size(); i++) {
        if (maxCycle < tp[i].size())
            maxCycle = tp[i].size();
    }
    QMap<int, int> result;
    while (maxCycle != 0) {
        result.insert(maxCycle, 0);
        maxCycle--;
    }
    for (int i = 0; i < tp.size(); i++) {
        result[tp[i].size()]++;
    }
    QString str = "[";
    for (int i = 1; i <= result.size(); i++) {
        if (result[i] != 0) {
            if (i != result.size())
                str += QString::number(i) + "^" + QString::number(result[i]) + ",";
            else str += QString::number(i) + "^" + QString::number(result[i]);
        }
    }
    str += "]";
    return str;
}
int TranspositionGroup::getHaos()
{
    std::vector<std::pair<int, int>> result;
    for (size_t I = 0; I < tp.size(); I++) {
        for (size_t i = 0; i < tp[I].size(); i++) {
            if (tp[I].size() > 1) {
                if (i + 1 != tp[I].size())
                    result.push_back(std::make_pair(tp[I][i], tp[I][i + 1]));
                else result.push_back(std::make_pair(tp[I][i], tp[I][0]));
            } else {
                result.push_back(std::make_pair(tp[I][i], tp[I][i]));
            }
        }
    } std::sort(result.begin(), result.end());
    int count = 0;
    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = i; j < result.size() - 1; j++) {
            if (result[i].second > result[j + 1].second)
                count++;
        }
    }
    return count;
}

QString TranspositionGroup::getEven(bool forTest){
    if (forTest)
        return (getHaos() % 2) ? "Н" : "Ч";
    else return (getHaos() % 2) ? "Нечетная" : "Четная";
}

int TranspositionGroup::getOrder(){
    int order = tp[0].size();
    for (size_t i = 0; i < tp.size() - 1; i++) {
        order = LCM(order, tp[i + 1].size());
    }
    return order;
}

TranspositionGroup TranspositionGroup::simplify(int order){
    if (tp.size() > 1) {
        TranspositionGroup base(tp[0], order);
        for (int I = 1; I < tp.size(); I++) {
            TranspositionGroup tmp(tp[I], order);
            base = base * tmp;
        } tp = base.tp;
    } return *this;
}
