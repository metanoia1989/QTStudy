#ifndef AREA_H
#define AREA_H

#include <QObject>

class Area : public QObject
{
    Q_OBJECT
public:
    Area() {}
    ~Area() {}
    Area(const Area &area)
    {
        m_r = area.m_r;
    }
    Area(int r)
    {
        m_r = r;
    }
    double CountArea()
    {
        return 3.14*m_r*m_r;
    }

private:
    double m_r;
};

Q_DECLARE_METATYPE(Area)	// 将 Area 定义为元类型，所有基于模板的函数都可以识别

#endif // AREA_H
