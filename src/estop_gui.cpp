#include "estop_gui.h"
#include "ui_estop_gui.h"
#include <pluginlib/class_list_macros.h>

namespace rqt_estop {

estop_gui::estop_gui()
    : rqt_gui_cpp::Plugin(), widget_(0)
{
   setObjectName("EStopGUI");
}

void estop_gui::initPlugin(qt_gui_cpp::PluginContext& context)
{
    // create QWidget
    widget_ = new QWidget();

    // access standalone command line arguments
    QStringList argv = context.argv();

    // extend the widget with all attributes and children from UI file
    ui_.setupUi(widget_);
    // add widget to the user interface
    context.addWidget(widget_);



    //Publisher
    cmd_vel_pub_ = getNodeHandle().advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // Subscriber
    cmd_vel_estop_sub_ = getNodeHandle().subscribe<geometry_msgs::Twist>("/cmd_vel_estop", 10, &estop_gui::cmd_velCallback, this);

    // Fill out zero message
    zero_twist_.linear.x = 0.0;
    zero_twist_.linear.y = 0.0;
    zero_twist_.linear.z = 0.0;
    zero_twist_.angular.x = 0.0;
    zero_twist_.angular.y = 0.0;
    zero_twist_.angular.z = 0.0;

    // Set EStop to active (checked)
    ui_.estop_button->setCheckable(true);
    ui_.estop_button->setChecked(true);
    estopActive();

    // CONNECTIONS
    connect(ui_.estop_button, SIGNAL( toggled(bool) ), this, SLOT( on_estop_button_toggled(bool) ) );
}

void estop_gui::shutdownPlugin()
{
    // TODO unregister all publishers here
    cmd_vel_pub_.shutdown();

}

void estop_gui::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
{
  // TODO save intrinsic configuration, usually using:
  // instance_settings.setValue(k, v)
}

void estop_gui::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
{
  // TODO restore intrinsic configuration, usually using:
  // v = instance_settings.value(k)
}

void estop_gui::estopActive()
{
    ui_.estop_button->setStyleSheet("background-color: rgb(0,255,0); color: black;");
    ui_.estop_button->setText("GO");
    ui_.status_text->setText("EStop active!");
    cmd_vel_pub_.publish(zero_twist_);
}

void estop_gui::estopInactive()
{
    ui_.estop_button->setStyleSheet("background-color: red; color: white; font: 20pt \"Ubuntu\";");
    ui_.estop_button->setText("STOP");
    ui_.status_text->setText("Robots running...");
}

void estop_gui::cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    // Republish if emergency stop in not activated
    if (not ui_.estop_button->isChecked())
        cmd_vel_pub_.publish(msg);
}

void rqt_estop::estop_gui::on_estop_button_toggled(bool checked)
{
    if (checked)
        estopActive();
    else
        estopInactive();
}


}   // namespace
PLUGINLIB_EXPORT_CLASS(rqt_estop::estop_gui, rqt_gui_cpp::Plugin)

