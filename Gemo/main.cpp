#include "Geometry.h"

int main()
{
    Vector2D point1(4,4),point0(0,0);
    Vector2D p3(0,2),p4(2,0);

    Line2D line1(point0,point1);
    Line2D line2(1,0,-1);
    Circle2D circle(point1,2.0);
    Rect2D rect(p3,p4);

    cout<<"����ֱ�߽��㣺"<<line1.intersection(line2);
    cout<<"ֱ����Բ�Ľ��������"
        <<circle.intersection(line1,p3,p4)<<endl;
    cout<<p3<<p4;
    cout<<"������ֱ�ߵĽ��������"
        <<rect.intersection(line1,p3,p4)<<endl;
    cout<<p3<<p4;

    return 0;
}

