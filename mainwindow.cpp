#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>

#include <vector>
#include <set>
#include <chrono>
#include <string>
#include <algorithm>


constexpr int IMG_HEIGHT=700;//associated with y axis
constexpr int IMG_WIDTH=700;//associated with x axis


QImage img=QImage(IMG_WIDTH,IMG_HEIGHT,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));
    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


int global_x,global_y;

int global_center_x,global_center_y;
int global_radius;
int global_rx,global_ry;


int grid_len=20;
std::vector<std::set<std::pair<int,int>>> lines_list;//store as (y,x) for searching

std::vector<std::vector<int>> is_filled(IMG_WIDTH/grid_len,std::vector<int>(IMG_HEIGHT/grid_len,0));
std::vector<std::vector<QRgb>> colors(IMG_WIDTH/grid_len,std::vector<QRgb>(IMG_HEIGHT/grid_len,qRgb(0,0,0)));
struct clip_struct{
    int x_max,x_min,y_max,y_min;
    bool in_window(int x,int y){
        return x>=x_min and x<=x_max and y>=y_min and y<=y_max;
    }
    int give_code(const std::pair<int,int>& p){
        int bit_val=0;//udrl
        if(p.second>y_max){
            bit_val^=(1<<3);
        }
        if(p.second<y_min){
            bit_val^=(1<<2);
        }
        if(p.first>x_max){
            bit_val^=(1<<1);
        }
        if(p.first<x_min){
            bit_val^=(1<<0);
        }

        return bit_val;
    }
    std::pair<int,int> clip_point_within(std::pair<int,int> p){
        int x=p.first;
        int y=p.second;

        return {
            std::max(std::min(x_max,x),x_min),
            std::max(std::min(y_max,y),y_min)
        };
    }
    bool is_inside_line(std::pair<int,int> p,char c){
        switch (c) {
            case 'L':
                return p.first>=x_min;
            case 'R':
                return p.first<=x_max;
            case 'B':
                return p.second>=y_min;
            case 'T':
                return p.second<=y_max;
            default:
                return false;
        }
    }
};

struct polygon{
    std::vector<std::pair<int,int>> points;
};

std::pair<int,int> last_vertex={-1,-1};
polygon g_pol;
clip_struct g_clip_window;

std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> line_points;

std::pair<int,int> give_box(int x,int y){
    int box_x=x/grid_len;
    int box_y=y/grid_len;

    return {box_x,box_y};
}

void MainWindow::toggle_box(std::pair<int,int> p,QRgb color_now){
    if(is_filled[p.first][p.second]){
        color_now=qRgb(0,0,0);
    }
    fill_box(p,color_now);
}


void MainWindow::fill_box(std::pair<int,int> p, QRgb color_now){
    int box_x=p.first;
    int box_y=p.second;
    if(color_now==qRgb(0,0,0)){
        is_filled[p.first][p.second]=0;
    }else{
        is_filled[p.first][p.second]=1;
    }
    colors[p.first][p.second]=color_now;
    for(int i=1;i<grid_len;++i){
        for(int j=1;j<grid_len;++j){
//            img.setPixel(box_x*grid_len+i,box_y*grid_len+j,qRgb(255,255,255));
//            std::cout<<"filling now: "<<box_x*grid_len+i<<" "<<box_y*grid_len+j<<std::endl;
            img.setPixel(box_x*grid_len+i,box_y*grid_len+j,color_now);
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}




void MainWindow::point(int x,int y)
{

    img.setPixel(x,y,qRgb(255,255,0));
    ui->frame->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::showMousePosition(QPoint &pos)
{
    auto box=give_box(pos.x(),pos.y());
    ui->mouse_movement->setText(" X : "+QString::number(box.first-axis_boxes.first)+", Y : "+QString::number(-(box.second-axis_boxes.second)));
//    ui->mouse_movement->setText(" X : "+QString::number(pos.x())+", Y : "+QString::number(pos.y()));
}
void MainWindow::Mouse_Pressed()
{
    global_x=ui->frame->x;
    global_y=ui->frame->y;

    ui->mouse_pressed->setText(" X : "+QString::number(ui->frame->x)+", Y : "+QString::number(ui->frame->y));
//    point(ui->frame->x,ui->frame->y);

    auto box_loc=give_box(ui->frame->x,ui->frame->y);
    if(ui->show_axes->isChecked()){
        draw_axes(qRgb(0,0,0));
//        axis_boxes=box_loc;
        axis_boxes={(IMG_WIDTH/grid_len)/2,(IMG_HEIGHT/grid_len)/2};
        draw_axes();
    }else{
        toggle_box(box_loc);
    }



//    ui->x_axis->move(0,ui->frame->y);
//    ui->y_axis->move(ui->frame->x,0);
}

void MainWindow::draw_axes(QRgb color_now){
//    auto color_now=qRgb(0,0,0);
    for(int i=0;i<IMG_WIDTH/grid_len;++i){
        fill_box({i,axis_boxes.second},color_now);
    }
    for(int j=0;j<IMG_HEIGHT/grid_len;++j){
        fill_box({axis_boxes.first,j},color_now);
    }
}

void MainWindow::on_show_axes_clicked()
{
//    if(ui->show_axes->isChecked()){
//        ui->x_axis->show();
//        ui->y_axis->show();
//    }
//    else{
//        ui->x_axis->hide();
//        ui->y_axis->hide();
//    }
}
void MainWindow::on_set_point1_clicked()
{
//    p1.setX(round(global_x/(double)grid_d)*grid_d);
//    p1.setY(round(global_y/(double)grid_d)*grid_d);
    first_point=give_box(global_x,global_y);
    if(ui->draw_line->isChecked()){
        p1.setX(ui->frame->x);
        p1.setY(ui->frame->y);
    }
}

void MainWindow::on_set_point2_clicked()
{
//    p2.setX(round(global_x/(double)grid_d)*grid_d);
//    p2.setY(round(global_y/(double)grid_d)*grid_d);
    second_point=give_box(global_x,global_y);
    if(ui->draw_line->isChecked()){
        p2.setX(ui->frame->x);
        p2.setY(ui->frame->y);
    }
}

void MainWindow::on_Draw_clicked()
{
    int r0=ui->circle_radius->value();
    QPainter painter(&img);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    if(ui->draw_circle->isChecked()){
        p1.setX(ui->frame->x);
        p1.setY(ui->frame->y);
        painter.setPen(pen);
        painter.drawEllipse(p1,r0,r0);
    }
    if(ui->draw_line->isChecked()){
        painter.setPen(Qt::red);
        painter.drawLine(p1,p2);
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_clicked()//reset
{
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
//            img.setPixel(i,j,qRgb(255,255,255));
        }
    }
    for(auto& v:is_filled){
        for(auto& x:v){
            x=0;
        }
    }

    for(auto& v:colors){
        for(auto& x:v){
            x=qRgb(0,0,0);
        }
    }
    line_points.clear();
    g_pol.points.clear();
    last_vertex={-1,-1};

    ui->frame->setPixmap(QPixmap::fromImage(img));
}



void MainWindow::on_pushButton_2_clicked()
{
//    for(int j=0;j<img.height();j+=grid_d)
//    {
//        for(int i=0;i<img.width();i++)
//        {
////            img.setPixel(i,j,qRgb(0,0,0));
//              img.setPixel(i,j,qRgb(255,255,255));
//        }
//    }
//    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_3_clicked()
{
    for(int j=0;j<img.height();j+=grid_len)
    {
        for(int i=0;i<img.width();i++)
        {
//            img.setPixel(i,j,qRgb(0,0,0));
              img.setPixel(i,j,qRgb(255,255,255));
        }
    }
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i+=grid_len)
        {
//            img.setPixel(i,j,qRgb(0,0,0));
              img.setPixel(i,j,qRgb(255,255,255));
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_4_clicked()//dda
{
   auto time_point1=std::chrono::high_resolution_clock::now();

   auto blue_color=qRgb(0,0,255);

   std::set<std::pair<int,int>> all_points;
   double x0=first_point.first;
   double y0=first_point.second;

   double x1=second_point.first;
   double y1=second_point.second;

   if(x0==x1){//vertical m=inf
       if(y0>y1){
           std::swap(y0,y1);
       }
       for(int y=y0;y<=y1;++y){
           if(in_map(x0,y)){
               fill_box({x0,y},blue_color);
               all_points.insert({y,x0});
           }
       }
   }else{
       double m=(y0-y1)/(x0-x1);
       if(abs(m)<=1){
           //x is increasing
           if(x0>x1){
               std::swap(x0,x1);
               std::swap(y0,y1);
           }
           double x=x0;
           double y=y0;
           while(x<=x1){
               if(in_map(x,y)){
                   fill_box({x,y},blue_color);
                   all_points.insert({y,x});
               }
               x++;
               y+=m;
           }
       }else{
           //y is increasing
           if(y0>y1){
               std::swap(x0,x1);
               std::swap(y0,y1);
           }
           double inv_m=1/m;
           double x=x0;
           double y=y0;
           while(y<=y1){
               if(in_map(x,y)){
                   fill_box({x,y},blue_color);
                   all_points.insert({y,x});
               }
               y++;
               x+=inv_m;
           }
       }
   }

   lines_list.push_back(all_points);
//   std::cout<<"LINE"<<std::endl;
//   for(auto p:all_points){
//       std::cout<<p.second<<" "<<p.first<<std::endl;
//   }
   auto time_point2=std::chrono::high_resolution_clock::now();

   auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
   std::string s=std::to_string(total_time);
   s+=" milliseconds taken";
   ui->label->setText(QString(s.c_str()));
}

void MainWindow::on_pushButton_5_clicked()
{
    auto time_point1=std::chrono::high_resolution_clock::now();
    //write the process here

    auto green_color=qRgb(0,255,0);

    int dx=abs(second_point.first-first_point.first);
    int dy=abs(second_point.second-first_point.second);
//    std::cout<<dx<<" "<<dy<<"\n";
    int x=first_point.first;
    int y=first_point.second;


//    if(dx<0){
//        x=second_point.first;
//        y=second_point.second;
//        x_end=first_point.first;
//    }
    auto i1=2*dy;
    auto i2=2*dy-2*dx;

    int p=2*dy-dx;

    for (int i = 0; i <= dx; i++)
    {
        if(x>=0 and y>=0 and x<IMG_WIDTH/grid_len and y<IMG_HEIGHT/grid_len){
            fill_box({x,y},green_color);
//            std::cout<<x<<" "<<y<<std::endl;
        }
        if(x<second_point.first){
            x++;
        }else{
            x--;
        }

        if (p < 0)
        {
//            fill_box({x,y},green_color);
            p+=i1;
        }
        else
        {
            if(y<second_point.second){
                y++;
            }else{
                y--;
            }
//            fill_box({x,y},green_color);
            p+=i2;
        }
    }
    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);

    //    QThread::msleep(1000);
}

void MainWindow::on_pushButton_6_clicked()
{
    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,0,255);

    double theta=0;
    double theta_end=(22.0/7)/2;
//    int r=5; //fixed for now
    int r=global_radius;

    double step=0.01;
    auto time_point1=std::chrono::high_resolution_clock::now();
    auto draw_eight_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
                cur_x=sign_x*y+xc;
                cur_y=sign_y*x+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
            }
        }
    };
    std::set<std::pair<int,int>> done;
    while(theta<=theta_end){
        int x=floor(r*cos(theta));
        int y=floor(r*sin(theta));
        theta+=step;
        if(!done.insert({x,y}).second){
            continue;
        }
        std::cout<<x<<" "<<y<<"\n";
        draw_eight_points(x,y);

    }
    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}


void MainWindow::on_radius_input_textChanged()
{
    global_radius=(ui->radius_input->toPlainText().toInt());
}

void MainWindow::on_pushButton_7_clicked()
{
    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,255,0);

    int r=global_radius;
    auto time_point1=std::chrono::high_resolution_clock::now();
    auto draw_eight_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
                cur_x=sign_x*y+xc;
                cur_y=sign_y*x+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
            }
        }
    };
    int x=0;
    int y=r;
    int d=3-2*r;

    std::set<std::pair<int,int>> done;
    if(done.insert({x,y}).second){
        draw_eight_points(x,y);
    }
    while(x<=r){

        if(d<=0){
            d=d+(4*x)+6;
        }
        else{
            d=d+(4*x)-(4*y)+10;
            y=y-1;
        }
        x=x+1;
        if(done.insert({x,y}).second){
            draw_eight_points(x,y);
        }
    }
    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}

void MainWindow::on_pushButton_8_clicked()//midpoint circle button
{
    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,255,0);

    int r=global_radius;
    auto time_point1=std::chrono::high_resolution_clock::now();

    auto draw_eight_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
                cur_x=sign_x*y+xc;
                cur_y=sign_y*x+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
            }
        }
    };

    int p=1-r;
    int x=0;
    int y=r;
    while(x<=y){
        draw_eight_points(x,y);
        ++x;
        if(p>=0){
            y--;
            p+=(2*x+1-2*y);
        }else{
            p+=(2*x+1);
        }
    }

    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}





void MainWindow::on_pushButton_9_clicked()//cartesian method
{
    std::cout<<"Called this function"<<std::endl;
    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,255,0);

    int r=global_radius;
    auto draw_eight_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
                cur_x=sign_x*y+xc;
                cur_y=sign_y*x+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
            }
        }
    };

    int x=0;
    auto time_point1=std::chrono::high_resolution_clock::now();
    while(true){
        int y=sqrt(r*r-x*x);
        if(x>y){
            break;
        }
        draw_eight_points(x,y);
        x++;
    }

    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}

void MainWindow::on_pushButton_10_clicked()//again cartesian
{
//    std::cout<<"Called this function"<<std::endl;
    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,255,0);

    int r=global_radius;
    auto draw_eight_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
                cur_x=sign_x*y+xc;
                cur_y=sign_y*x+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
            }
        }
    };

    int x=0;
    auto time_point1=std::chrono::high_resolution_clock::now();
    while(true){
        int y=sqrt(r*r-x*x);
        if(x>y){
            break;
        }
        draw_eight_points(x,y);
        x++;
    }

    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}


void MainWindow::on_pushButton_11_clicked()//ellipse drawing algo
{
    double dx, dy, d1, d2, x, y;
    double rx=global_rx;
    double ry=global_ry;

    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,255,0);
    std::cout<<rx<<std::endl;
    std::cout<<ry<<std::endl;
    x = 0;
    y = ry;

    auto draw_4_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
            }
        }
    };


    auto time_point1=std::chrono::high_resolution_clock::now();

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) +
                     (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy)
    {

        // Print points based on 4-way symmetry
        draw_4_points(x,y);

        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
          (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0)
    {

        // Print points based on 4-way symmetry
        draw_4_points(x,y);

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}

void MainWindow::on_RxInput_textChanged()
{
    global_rx=(ui->RxInput->toPlainText().toInt());
}

void MainWindow::on_RyInput_textChanged()
{
    global_ry=(ui->RyInput->toPlainText().toInt());
}

void MainWindow::on_pushButton_12_clicked()
{
    double dx, dy, d1, d2, x, y;
    double rx=global_rx;
    double ry=global_ry;

    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,255,0);
    std::cout<<rx<<"\n";
    std::cout<<ry<<"\n";
    x = 0;
    y = ry;

    auto draw_4_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
                    delay();
                }
            }
        }
    };


    auto time_point1=std::chrono::high_resolution_clock::now();

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) +
                     (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy)
    {

        // Print points based on 4-way symmetry
        draw_4_points(x,y);

        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
          (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0)
    {

        // Print points based on 4-way symmetry
        draw_4_points(x,y);

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}



void MainWindow::on_pushButton_13_clicked()
{
    int xc=first_point.first;
    int yc=first_point.second;
    auto color_now=qRgb(0,0,255);


    double theta=0;
    double theta_end=(22.0/7)/2;
    double rx=global_rx;
    double ry=global_ry;
    std::cout<<rx<<" "<<ry<<std::endl;

    double step=0.05;
    auto time_point1=std::chrono::high_resolution_clock::now();
    auto draw_4_points=[&](int x,int y){
        for(auto sign_x:{-1,1}){
            for(auto sign_y:{-1,1}){
                int cur_x=sign_x*x+xc;
                int cur_y=sign_y*y+yc;
                if(cur_x>=0 and cur_x<IMG_WIDTH/grid_len and cur_y>=0 and cur_y<IMG_HEIGHT/grid_len){
                    fill_box({cur_x,cur_y},color_now);
//                    delay();
                }
            }
        }
    };

    while(theta<=theta_end){
        int x=floor(rx*cos(theta));
        int y=floor(ry*sin(theta));
        theta+=step;
        std::cout<<x<<" "<<y<<std::endl;
        draw_4_points(x,y);
    }
    auto time_point2=std::chrono::high_resolution_clock::now();
    auto total_time=std::chrono::duration_cast<std::chrono::milliseconds>(time_point2-time_point1).count();
    std::string s=std::to_string(total_time);
    s+=" milliseconds taken";
    ui->label->setText(QString(s.c_str()));
}

bool MainWindow::in_map(int x,int y){
    return (x>=0 and x<IMG_WIDTH/grid_len and y>=0 and y<IMG_HEIGHT/grid_len);
}

void MainWindow::on_pushButton_14_clicked()//flood_fill_4
{
    int x0=first_point.first;
    int y0=first_point.second;
    auto color_now=qRgb(199, 80, 189);

    std::vector<std::pair<int,int>> dir={
        {0,1},
        {0,-1},
        {1,0},
        {-1,0},
    };
    auto dfs=[&](int x,int y,auto dfs)->void{
        for(auto p:dir){
            int new_x=x+p.first;
            int new_y=y+p.second;
            if(!in_map(new_x,new_y)){
                continue;
            }
            if(is_filled[new_x][new_y]){
                continue;
            }
            fill_box({new_x,new_y},color_now);
            delay();
            dfs(new_x,new_y,dfs);
        }
    };

    dfs(x0,y0,dfs);
}



void MainWindow::on_pushButton_15_clicked()//flood_fill_8
{
    int x0=first_point.first;
    int y0=first_point.second;
    auto color_now=qRgb(199, 80, 189);//pink color

    std::vector<std::pair<int,int>> dir={
        {0,1},
        {0,-1},
        {1,0},
        {-1,0},
        {1,1},
        {1,-1},
        {-1,1},
        {-1,-1},
    };
    auto dfs=[&](int x,int y,auto dfs)->void{
        for(auto p:dir){
            int new_x=x+p.first;
            int new_y=y+p.second;
            if(!in_map(new_x,new_y)){
                continue;
            }
            if(is_filled[new_x][new_y]){
                continue;
            }
            fill_box({new_x,new_y},color_now);
            delay();
            dfs(new_x,new_y,dfs);
        }
    };

    dfs(x0,y0,dfs);
}


void MainWindow::on_pushButton_16_clicked()//boundary_fill_4
{
    auto bound_color=qRgb(0,0,255);//blue color
    auto color_now=qRgb(199, 80, 189);//pink color
    int x0=first_point.first;
    int y0=first_point.second;


    std::vector<std::pair<int,int>> dir={
        {0,1},
        {0,-1},
        {1,0},
        {-1,0},
    };
    auto dfs=[&](int x,int y,auto dfs)->void{
        for(auto p:dir){
            int new_x=x+p.first;
            int new_y=y+p.second;
            if(!in_map(new_x,new_y)){
                continue;
            }
            if(colors[new_x][new_y]==color_now or colors[new_x][new_y]==bound_color){
                continue;
            }
            fill_box({new_x,new_y},color_now);
            delay();
            dfs(new_x,new_y,dfs);
        }
    };

    dfs(x0,y0,dfs);
}

void MainWindow::on_pushButton_17_clicked()//boundary_fill_8
{
    auto bound_color=qRgb(0,0,255);//blue color
    auto color_now=qRgb(199, 80, 189);//pink color
    int x0=first_point.first;
    int y0=first_point.second;


    std::vector<std::pair<int,int>> dir={
        {0,1},
        {0,-1},
        {1,0},
        {-1,0},
        {1,1},
        {1,-1},
        {-1,1},
        {-1,-1},
    };
    auto dfs=[&](int x,int y,auto dfs)->void{
        for(auto p:dir){
            int new_x=x+p.first;
            int new_y=y+p.second;
            if(!in_map(new_x,new_y)){
                continue;
            }
            if(colors[new_x][new_y]==color_now or colors[new_x][new_y]==bound_color){
                continue;
            }
            fill_box({new_x,new_y},color_now);
            delay();
            dfs(new_x,new_y,dfs);
        }
    };

    dfs(x0,y0,dfs);

}



void MainWindow::on_pushButton_18_clicked()//reset lines_list
{
    lines_list.clear();
}



void MainWindow::on_pushButton_19_clicked()//scanline
{

//    std::cout<<"here"<<std::endl;
//    for(auto s:lines_list){
//        std::cout<<"LINE: "<<std::endl;
//        for(auto p:s){
//            std::cout<<p.second<<" "<<p.first<<" "<<std::endl;
//        }
//    }
    std::set<std::pair<int,int>> all_borders;
    for(auto s:lines_list){
        for(auto p:s){
            all_borders.insert({p.second,p.first});
        }
    }
    auto color_now=qRgb(199, 80, 189);//pink color

    auto handle_sign=[&](int y_fixed,int y){
        if(y<y_fixed){
            return 1;
        }else if(y>y_fixed){
            return -1;
        }else{
            return 0;
        }
    };

    //do for all y's
    for(int y=0;y<IMG_HEIGHT/grid_len;++y){
        std::map<int,std::vector<int>> mappa;
        for(auto& s:lines_list){
            //see if the point exists in s
            auto it=s.lower_bound({y,-1});//will catch y for any x
            if(it!=s.end() and it->first==y){//valid point selected
                if(*it==*(--s.end())){//last point
                    auto another_y=s.begin()->first;
                    mappa[it->second].push_back(handle_sign(y,another_y));
                }else if(*it==*s.begin()){//first point
                    auto another_y=(--s.end())->first;
                    mappa[it->second].push_back(handle_sign(y,another_y));
                }else{
                    mappa[it->second].push_back(-2);
                }
            }
        }
        std::vector<int> points_list;
        for(auto& p:mappa){
            bool neg=0;
            bool pos=0;
            for(auto x:p.second){
                if(x==-1){
                    neg=1;
                }else if(x==1){
                    pos=1;
                }else if(x==0){

                }
            }
            if((neg and  pos) or (!neg and !pos)){//different side or NA
                points_list.push_back(p.first);
            }else{//same side
                points_list.push_back(p.first);
                points_list.push_back(p.first);
            }
        }
        if(points_list.size()){
            for(auto x:points_list){
                std::cout<<x<<" ";
            }
            std::cout<<std::endl;
        }

        for(int i=0;i<(int)points_list.size()-1;++i){
            if(!(i&1)){//draw
                for(int x=points_list[i]+1;x<points_list[i+1];++x){
                    if(!all_borders.count({x,y})){
                        fill_box({x,y},color_now);
                        delay();
                    }

                }
            }
        }
    }
}




std::vector<std::vector<int>> matmul(const std::vector<std::vector<double>>& a,
                                const std::vector<std::vector<int>>& b){
    int n=a.size();
    int m=a[0].size();
    int p=b[0].size();

    std::vector<std::vector<int>> ans(n,std::vector<int>(p));
    for(int i=0;i<n;++i){
        for(int j=0;j<p;++j){
            double val=0;
            for(int k=0;k<m;++k){
                val+=a[i][k]*b[k][j];
            }
            ans[i][j]=round(val);
        }
    }

    return ans;
}

std::pair<int,int> MainWindow::convert_to_xy(int i,int j){
    int x=i-axis_boxes.first;
    int y=-(j-axis_boxes.second);

//    std::cout<<x<<" "<<y<<std::endl;

    return {x,y};
}

std::pair<int,int> MainWindow::convert_to_ij(int x,int y){
    int i=x+axis_boxes.first;
    int j=axis_boxes.second-y;

    return {i,j};
}

void MainWindow::on_pushButton_20_clicked()//rotate
{
    double angle=(ui->textEdit->toPlainText().toDouble());
    angle=(22.0/7)*angle/180;
    std::vector<std::vector<double>> rot_mat={
        {cos(angle),-sin(angle),0},
        {sin(angle),cos(angle),0},
        {0,0,1},
    };

    int color_n=colors.size();
    int color_m=colors[0].size();

    std::vector<std::vector<QRgb>> new_color=std::vector<std::vector<QRgb>>(color_n,std::vector<QRgb>(color_m));
    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            if(colors[i][j]==qRgb(0,0,0) or colors[i][j]==axis_color){
                continue;
            }
            auto pair1=convert_to_xy(i,j);
            int x=pair1.first;
            int y=pair1.second;
            auto new_point=matmul(rot_mat,{{x},{y},{1}});
            auto pair2=convert_to_ij(new_point[0][0],new_point[1][0]);
            int new_i=pair2.first;
            int new_j=pair2.second;

            if(in_map(new_i,new_j)){
                new_color[new_i][new_j]=colors[i][j];
            }
        }
    }

    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            fill_box({i,j},new_color[i][j]);
//            colors[i][j]=new_color[i][j];
        }
    }

    draw_axes();



}

void MainWindow::on_pushButton_21_clicked()//translation
{
    int xh=ui->textEdit_2->toPlainText().toDouble();
    int yh=ui->textEdit_3->toPlainText().toDouble();

    std::vector<std::vector<double>> tran_mat={
        {1,0,(double)xh},
        {0,1,(double)yh},
        {0,0,1},
    };

    int color_n=colors.size();
    int color_m=colors[0].size();

    std::vector<std::vector<QRgb>> new_color=std::vector<std::vector<QRgb>>(color_n,std::vector<QRgb>(color_m));
    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            if(colors[i][j]==qRgb(0,0,0) or colors[i][j]==axis_color){
                continue;
            }
            auto pair1=convert_to_xy(i,j);
            int x=pair1.first;
            int y=pair1.second;
            auto new_point=matmul(tran_mat,{{x},{y},{1}});
            auto pair2=convert_to_ij(new_point[0][0],new_point[1][0]);
            int new_i=pair2.first;
            int new_j=pair2.second;

            if(in_map(new_i,new_j)){
                new_color[new_i][new_j]=colors[i][j];
            }
        }
    }

    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            fill_box({i,j},new_color[i][j]);
        }
    }

    draw_axes();
}



void MainWindow::on_pushButton_22_clicked()//shear
{
    double hx=ui->textEdit_4->toPlainText().toDouble();
    double hy=ui->textEdit_5->toPlainText().toDouble();

    std::vector<std::vector<double>> shear_mat={
        {1,hx,},
        {hy,1,0},
        {0,0,1},
    };

    int color_n=colors.size();
    int color_m=colors[0].size();

    std::vector<std::vector<QRgb>> new_color=std::vector<std::vector<QRgb>>(color_n,std::vector<QRgb>(color_m));
    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            if(colors[i][j]==qRgb(0,0,0) or colors[i][j]==axis_color){
                continue;
            }
            auto pair1=convert_to_xy(i,j);
            int x=pair1.first;
            int y=pair1.second;
            auto new_point=matmul(shear_mat,{{x},{y},{1}});
            auto pair2=convert_to_ij(new_point[0][0],new_point[1][0]);
            int new_i=pair2.first;
            int new_j=pair2.second;

            if(in_map(new_i,new_j)){
                new_color[new_i][new_j]=colors[i][j];
            }
        }
    }

    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            fill_box({i,j},new_color[i][j]);
        }
    }

    draw_axes();
}

void MainWindow::on_pushButton_23_clicked()//scale
{
    double sx=ui->textEdit_6->toPlainText().toDouble();
    double sy=ui->textEdit_7->toPlainText().toDouble();
    std::cout<<sx<<" "<<sy<<std::endl;
    std::vector<std::vector<double>> scale_mat={
        {sx,0,},
        {0,sy,0},
        {0,0,1},
    };

    int color_n=colors.size();
    int color_m=colors[0].size();

    std::vector<std::vector<QRgb>> new_color=std::vector<std::vector<QRgb>>(color_n,std::vector<QRgb>(color_m,qRgb(0,0,0)));
    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            if(colors[i][j]==qRgb(0,0,0) or colors[i][j]==axis_color){
                continue;
            }
            auto pair1=convert_to_xy(i,j);
            int x=pair1.first;
            int y=pair1.second;
            auto new_point=matmul(scale_mat,{{x},{y},{1}});
            auto pair2=convert_to_ij(new_point[0][0],new_point[1][0]);
            int new_i=pair2.first;
            int new_j=pair2.second;

            if(in_map(new_i,new_j)){
                new_color[new_i][new_j]=colors[i][j];
            }
        }
    }

    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            fill_box({i,j},new_color[i][j]);
        }
    }

    draw_axes();
}



void MainWindow::on_pushButton_24_clicked()//rotate wrt
{
    int x=ui->textEdit_8->toPlainText().toDouble();
    int y=ui->textEdit_9->toPlainText().toDouble();
    double angle=ui->textEdit_10->toPlainText().toDouble();


    //translate
    ui->textEdit_2->setText(QString::number(-x));
    ui->textEdit_3->setText(QString::number(-y));

    on_pushButton_21_clicked();

    //rotate
    ui->textEdit->setText(QString::number(angle));
    on_pushButton_20_clicked();

    //translate back
    ui->textEdit_2->setText(QString::number(x));
    ui->textEdit_3->setText(QString::number(y));
    on_pushButton_21_clicked();


}



void MainWindow::on_pushButton_25_clicked()//shear wrt
{
    int x=ui->textEdit_11->toPlainText().toDouble();
    int y=ui->textEdit_12->toPlainText().toDouble();
    double sx=ui->textEdit_13->toPlainText().toDouble();
    double sy=ui->textEdit_14->toPlainText().toDouble();

    //translate
    ui->textEdit_2->setText(QString::number(-x));
    ui->textEdit_3->setText(QString::number(-y));

    on_pushButton_21_clicked();

    //shear
    ui->textEdit_4->setText(QString::number(sx));
    ui->textEdit_5->setText(QString::number(sy));
    on_pushButton_22_clicked();

    //translate back
    ui->textEdit_2->setText(QString::number(x));
    ui->textEdit_3->setText(QString::number(y));
    on_pushButton_21_clicked();
}

void MainWindow::on_pushButton_26_clicked()//create clip_window
{
    g_clip_window.x_min=first_point.first;
    g_clip_window.x_max=second_point.first;
    g_clip_window.y_min=first_point.second;
    g_clip_window.y_max=second_point.second;
}

void MainWindow::draw_line(const std::pair<int,int>& a,const std::pair<int,int>& b){
    first_point=a;
    second_point=b;
    on_pushButton_4_clicked();//dda

    line_points.push_back({a,b});
}



std::pair<std::pair<int,int>,std::pair<int,int>> clip_line_once(
        std::pair<std::pair<int,int>,std::pair<int,int>> line_point){
    int code1=g_clip_window.give_code(line_point.first);
    int code2=g_clip_window.give_code(line_point.second);
    if((code1==code2) and (code1==0)){
        return line_point;
    }
    if((code1&code2)){
        return line_point;
    }
    if(line_point.second.second-line_point.first.second==0 or line_point.second.first-line_point.first.first==0){
        return {
            g_clip_window.clip_point_within(line_point.first),
            g_clip_window.clip_point_within(line_point.second)
        };
    }
    double m=(line_point.second.second-line_point.first.second+0.0)/(line_point.second.first-line_point.first.first);
    if((code1|code2)&(1<<3)){//up
        //x=x1+1/m*(ymax-y1)
        std::pair<int,int>* pointer_point=&line_point.first;
        if(code2&(1<<3)){
            pointer_point=&line_point.second;
        }

        pointer_point->first=round(line_point.first.first+(1/m)*(g_clip_window.y_max-line_point.first.second));
        pointer_point->second=g_clip_window.y_max;

        return line_point;
    }else if((code1|code2)&(1<<2)){//down
        //x=x1+1/m*(ymin-y1)
        std::pair<int,int>* pointer_point=&line_point.first;
        if(code2&(1<<2)){
            pointer_point=&line_point.second;
        }

        pointer_point->first=round(line_point.first.first+(1/m)*(g_clip_window.y_min-line_point.first.second));
        pointer_point->second=g_clip_window.y_min;
        return line_point;
    }else if((code1|code2)&(1<<1)){//right
        //y=y1+m*(x_max-x1)
        std::pair<int,int>* pointer_point=&line_point.first;
        if(code2&(1<<1)){
            pointer_point=&line_point.second;
        }

        pointer_point->second=round(line_point.first.second+m*(g_clip_window.x_max-line_point.first.first));
        pointer_point->first=g_clip_window.x_max;
        return line_point;
    }else if((code1|code2)&(1<<0)){//left
        //y=y1+m*(x_min-x1)
        std::pair<int,int>* pointer_point=&line_point.first;
        if(code2&(1<<0)){
            pointer_point=&line_point.second;
        }

        pointer_point->second=round(line_point.first.second+m*(g_clip_window.x_min-line_point.first.first));
        pointer_point->first=g_clip_window.x_min;
        return line_point;
    }

    return line_point;
}


void MainWindow::on_pushButton_27_clicked()//clipLine
{
    std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> new_points;
    for(auto v:line_points){
        int code1=g_clip_window.give_code(v.first);
        int code2=g_clip_window.give_code(v.second);
        if((code1&code2)){//outside fully
            continue;
        }
        for(int i=0;i<4;++i){
            v=clip_line_once(v);
        }
        new_points.push_back(v);
    }

    on_pushButton_clicked();//reset;
    on_pushButton_3_clicked();//grids;
    draw_axes();
    on_pushButton_28_clicked();//drawWindow;
    for(auto p:new_points){
        draw_line(p.first,p.second);
    }

}

void MainWindow::on_pushButton_28_clicked()//drawWindow
{
    auto red_color=qRgb(255,0,0);
    for(int x=g_clip_window.x_min;x<=g_clip_window.x_max;++x){
        fill_box({x,g_clip_window.y_min},red_color);
        fill_box({x,g_clip_window.y_max},red_color);
    }

    for(int y=g_clip_window.y_min;y<=g_clip_window.y_max;++y){
        fill_box({g_clip_window.x_min,y},red_color);
        fill_box({g_clip_window.x_max,y},red_color);
    }
}

void MainWindow::on_pushButton_29_clicked()//drawLineForClipping
{
    draw_line(first_point,second_point);
}


void MainWindow::on_pushButton_30_clicked()//set vertex
{
    auto cur_point=give_box(global_x,global_y);
    if(last_vertex!=std::pair<int,int>(-1,-1)){
        first_point=cur_point;
        second_point=last_vertex;
        on_pushButton_4_clicked();//dda
    }
    last_vertex=cur_point;
    g_pol.points.push_back(last_vertex);
}

std::pair<int,int> get_intersection(std::pair<std::pair<int,int>,std::pair<int,int>> line_point,char c){


    if(c=='L' or c=='R'){
        //y=y1+m(x-x1)
        double m=(line_point.second.second-line_point.first.second+0.0)
                /(line_point.second.first-line_point.first.first);
        int x=g_clip_window.x_min;
        if(c=='R'){
            x=g_clip_window.x_max;
        }

        int y=round(line_point.first.second+m*(x-line_point.first.first));
        return {x,y};
    }else{
        //x=x1+1/m(y-y1)
        double inv_m=(line_point.second.first-line_point.first.first+0.0)
                /(line_point.second.second-line_point.first.second);
        int y=g_clip_window.y_min;
        if(c=='T'){
            y=g_clip_window.y_max;
        }

        int x=round(line_point.first.first+inv_m*(y-line_point.first.second));
        return {x,y};
    }
}


void MainWindow::on_pushButton_31_clicked()//clipPolygon
{
    std::vector<std::pair<int,int>> points;
    std::string op="LRBT";
    for(auto c:op){
        int n=g_pol.points.size();
        for(int i=0;i<n;++i){
            auto a=g_pol.points[i];
            auto b=g_pol.points[(i+1)%n];
            auto stat_a=g_clip_window.is_inside_line(a,c);
            auto stat_b=g_clip_window.is_inside_line(b,c);
//            std::cout<<a.first<<" "<<a.second<<" "<<stat_a<<"\n";
//            std::cout<<b.first<<" "<<b.second<<" "<<stat_b<<"\n";
            if(!stat_a and !stat_b){//outside
                //nothing
            }else if(stat_a and stat_b){//inside
                points.push_back(b);
            }else if(!stat_a and stat_b){//outside->inside
                auto intersection_point=get_intersection({a,b},c);
                points.push_back(intersection_point);
                points.push_back(b);
            }else{//inside->outside
                auto intersection_point=get_intersection({a,b},c);
                points.push_back(intersection_point);
            }
        }

        g_pol.points=points;
        points.clear();
    }
    points=g_pol.points;

    on_pushButton_clicked();//reset;
    on_pushButton_3_clicked();//grids;
    draw_axes();
    on_pushButton_28_clicked();//drawWindow;

    g_pol.points=points;
    int n=g_pol.points.size();
    for(int i=0;i<n;++i){

        auto a=g_pol.points[i];
//        std::cout<<a.first<<" "<<a.second<<"\n";
        auto b=g_pol.points[(i+1)%n];
        draw_line(a,b);
    }


}



void MainWindow::on_pushButton_32_clicked()//reflect_x
{
    std::vector<std::vector<double>> scale_mat={
        {-1,0,},
        {0,1,0},
        {0,0,1},
    };

    int color_n=colors.size();
    int color_m=colors[0].size();

    std::vector<std::vector<QRgb>> new_color=std::vector<std::vector<QRgb>>(color_n,std::vector<QRgb>(color_m,qRgb(0,0,0)));
    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            if(colors[i][j]==qRgb(0,0,0) or colors[i][j]==axis_color){
                continue;
            }
            auto pair1=convert_to_xy(i,j);
            int x=pair1.first;
            int y=pair1.second;
            auto new_point=matmul(scale_mat,{{x},{y},{1}});
            auto pair2=convert_to_ij(new_point[0][0],new_point[1][0]);
            int new_i=pair2.first;
            int new_j=pair2.second;

            if(in_map(new_i,new_j)){
                new_color[new_i][new_j]=colors[i][j];
            }
        }
    }

    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            fill_box({i,j},new_color[i][j]);
        }
    }

    draw_axes();
}

void MainWindow::on_pushButton_33_clicked()//reflect_y
{
    std::vector<std::vector<double>> scale_mat={
        {1,0,},
        {0,-1,0},
        {0,0,1},
    };

    int color_n=colors.size();
    int color_m=colors[0].size();

    std::vector<std::vector<QRgb>> new_color=std::vector<std::vector<QRgb>>(color_n,std::vector<QRgb>(color_m,qRgb(0,0,0)));
    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            if(colors[i][j]==qRgb(0,0,0) or colors[i][j]==axis_color){
                continue;
            }
            auto pair1=convert_to_xy(i,j);
            int x=pair1.first;
            int y=pair1.second;
            auto new_point=matmul(scale_mat,{{x},{y},{1}});
            auto pair2=convert_to_ij(new_point[0][0],new_point[1][0]);
            int new_i=pair2.first;
            int new_j=pair2.second;

            if(in_map(new_i,new_j)){
                new_color[new_i][new_j]=colors[i][j];
            }
        }
    }

    for(int i=0;i<color_n;++i){
        for(int j=0;j<color_m;++j){
            fill_box({i,j},new_color[i][j]);
        }
    }

    draw_axes();
}
