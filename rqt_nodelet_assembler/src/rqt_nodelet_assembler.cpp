/*
 * Software License Agreement (BSD License)
 *
 *   Copyright (c) 2016, Federico Spinelli (fspinelli@gmail.com)
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder(s) nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <rqt_nodelet_assembler/rqt_nodelet_assembler.h>
#include <pluginlib/class_list_macros.h>
#include <QFileDialog>

namespace rqt_nodelet_assembler
{

    NodeletAssembler::NodeletAssembler():
        rqt_gui_cpp::Plugin(),
        widget_(0)
    {
        setObjectName("NodeletAssembler");
    }

    void
    NodeletAssembler::initPlugin(qt_gui_cpp::PluginContext& context)
    {
        widget_= new QWidget();
        ui_.setupUi(widget_);
        if (context.serialNumber() > 1)
        {
            widget_->setWindowTitle(widget_->windowTitle() + " (" + QString::number(context.serialNumber()) + ")");
        }
        context.addWidget(widget_);
        //update packages and nodelets
        updatePluginList();
    }

    void
    NodeletAssembler::shutdownPlugin()
    {
    }

    void
    NodeletAssembler::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
    {
        //TODO
    }

    void
    NodeletAssembler::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
    {
        //TODO
    }

    QStringList
    NodeletAssembler::getNodeletsFromPlugin() const
    {
        //TODO
    }

    void
    NodeletAssembler::updatePluginList()
    {
        ui_.plugin_combo_box->clear();
        std::string n("nodelet");
        std::string p("plugin");
        ros::package::V_string vp;
        ros::package::getPlugins (n, p, vp, true);
        QStringList plist;
        for (size_t i=0; i<vp.size(); ++i)
            plist.append(vp[i].c_str());
        ui_.plugin_combo_box->insertItems(0, plist);
    }

    void
    NodeletAssembler::updateNodeletsList()
    {
        //TODO
    }

    void
    NodeletAssembler::onRefresh()
    {
        //TODO
    }

    void
    NodeletAssembler::onPackageChanged(int index)
    {
        //TODO
    }

    void
    NodeletAssembler::onNodeletChanged(int index)
    {
        //TODO
    }
}//End namespace

PLUGINLIB_EXPORT_CLASS(rqt_nodelet_assembler::NodeletAssembler, rqt_gui_cpp::Plugin)
