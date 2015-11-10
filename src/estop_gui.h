#ifndef rqt_estop__ESTOP_GUI_H
#define rqt_estop__ESTOP_GUI_H

#include <rqt_gui_cpp/plugin.h>
#include <ui_estop_gui.h>
#include <QWidget>
#include <QFlags>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"


namespace rqt_estop {

class estop_gui : public rqt_gui_cpp::Plugin
{
    Q_OBJECT

public:
    estop_gui();
    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
    virtual void shutdownPlugin();
    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

private:
    Ui::EstopWidget ui_;
    QWidget* widget_;
    geometry_msgs::Twist zero_twist_;

    void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg);
    void estopActive();
    void estopInactive();

protected:
    ros::Publisher cmd_vel_pub_;
    ros::Subscriber cmd_vel_estop_sub_;

private slots:
    void on_estop_button_toggled(bool checked);
};

} //namespace
#endif // rqt_estop__ESTOP_GUI_H
