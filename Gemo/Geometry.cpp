#include "Geometry.h"
#include <cmath>
#include <limits>
//����ļ������󽻵�ĺ���

//������ʼ��
const double Vector2D::error=std::numeric_limits< double >::max();
const Vector2D Vector2D::INVALIDATED( Vector2D::error, Vector2D::error );
const double Line2D::ERROR = std::numeric_limits< double >::max();

//����С��������ƽ����һԪ���η��̵Ľ�
inline double SQUARE( const double & val )
{
    return val * val;
}

inline int QUADRATIC_FOMULA( const double & a,const double & b,
                    const double & c,double & sol1,double & sol2 )
{
    double d = SQUARE( b ) - 4.0 * a * c;
    // ignore small noise
    if ( std::fabs( d ) < 1.0e-5 )
    {
        sol1 = -b / (2.0 * a);
        return 1;
    }
    else if ( d < 0.0 )
    {
        return 0;
    }
    else
    {
        d = std::sqrt( d );
        sol1 = (-b + d) / (2.0 * a);
        sol2 = (-b - d) / (2.0 * a);
        return 2;
    }
}

//�ù�ʽ������ֱ�ߵĽ���
Vector2D Line2D::intersection( const Line2D & line1,const Line2D & line2 )
{
    double tmp = line1.M_a * line2.M_b - line1.M_b * line2.M_a;
    if ( std::fabs( tmp ) < 1.0e-10 )    {
        return Vector2D::INVALIDATED;
    }

    return Vector2D( (line1.M_b * line2.M_c - line2.M_b * line1.M_c) / tmp,
                     (line2.M_a * line1.M_c - line1.M_a * line2.M_c) / tmp );
}

//����������ù�ʽ���һԪ���η��̣������ò�������
int Circle2D::intersection( const Line2D & line,Vector2D & sol1,Vector2D & sol2 ) const
{
    if ( std::fabs( line.a() ) < 1.0e-6 )
    {
        if ( std::fabs( line.b() ) < 1.0e-6 ) {
            std::cout << "Circle2D::intersection() illegal line."<< std::endl;
            return 0;
        }
        // Line:    By + C = 0  ---> y = -C/B
        // Circle:  (x - cx)^2 + (y - cy)^2 = r^2
        double x1 = 0.0, x2 = 0.0;
        int n_sol= QUADRATIC_FOMULA( 1.0,-2.0 * M_center.x(),
                                ( SQUARE( M_center.x() )
                                  + SQUARE( line.c() / line.b() + M_center.y() )
                                  - SQUARE( M_radius ) ),x1,x2 );
        if ( n_sol > 0 )
        {
            double y1 = -line.c() / line.b();

            sol1.assign( x1, y1 );

            if ( n_sol > 1 ){
                sol2.assign( x2, y1 );
            }
        }
        return n_sol;
    }
    else
    {
        // include (fabs(l.b()) < EPSILON) case
        // use line & circle formula
        //   Ax + By + C = 0
        //   (x - cx)^2 + (y - cy)^2 = r^2
        // make y's quadratic formula using these fomula.
        double m = line.b() / line.a();
        double d = line.c() / line.a();

        double a = 1.0 + m * m;
        double b = 2.0 * ( -M_center.y() + ( d + M_center.x() ) * m );
        double c = SQUARE( d + M_center.x() )
            + SQUARE( M_center.y() )
            - SQUARE( M_radius );

        double y1 = 0.0, y2 = 0.0;
        int n_sol = QUADRATIC_FOMULA( a, b, c,y1, y2 );

        if ( n_sol > 0 ) {
            sol1.assign( line.getX( y1 ), y1 );
        }

        if ( n_sol > 1 ) {
            sol2.assign( line.getX( y2 ), y2 );
        }

        return n_sol;
    }
}


//������ֱ���������߽��ߵĽ���
int Rect2D::intersection( const Line2D & line,
                Vector2D & sol1,Vector2D & sol2 ) const
{
    int n_sol = 0;
    Vector2D tsol[2];

    const double left_x = top_left.x();
    const double right_x = bottom_right.x();
    const double top_y = top_left.y();
    const double bottom_y = bottom_right.y();

    if ( n_sol < 2
         && ( tsol[n_sol] = leftEdge().intersection( line ) ).isValid()
         && top_y <= tsol[n_sol].y() && tsol[n_sol].y() <= bottom_y )
    {   ++n_sol;    }

    if ( n_sol < 2
         && ( tsol[n_sol] = rightEdge().intersection( line ) ).isValid()
         && top_y <= tsol[n_sol].y() && tsol[n_sol].y() <= bottom_y )
    {    ++n_sol;   }

    if ( n_sol < 2
         && ( tsol[n_sol] = topEdge().intersection( line ) ).isValid()
         && left_x <= tsol[n_sol].x() && tsol[n_sol].x() <= right_x )
    {   ++n_sol;    }

    if ( n_sol < 2
         && ( tsol[n_sol] = bottomEdge().intersection( line ) ).isValid()
         && left_x <= tsol[n_sol].x() && tsol[n_sol].x() <= right_x )
    {   ++n_sol;    }

    if ( n_sol == 2
         && std::fabs( tsol[0].x() - tsol[1].x() ) < 1.0e-5
         && std::fabs( tsol[0].y() - tsol[1].y() ) < 1.0e-5 )
    {   n_sol = 1;  }

    if ( n_sol > 0 )
    {
        sol1.assign(tsol[0].x(),tsol[0].y());
    }

    if ( n_sol > 1 )
    {
        sol2.assign(tsol[1].x(),tsol[1].y());
    }

    return n_sol;
}
