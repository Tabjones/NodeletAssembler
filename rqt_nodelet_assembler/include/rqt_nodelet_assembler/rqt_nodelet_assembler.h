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

#ifndef _INCL_RQT_NODELET_ASSEMBLER_H_
#define _INCL_RQT_NODELET_ASSEMBLER_H_

#include <rqt_gui_cpp/plugin.h>
#include <ros/package.h>
#include <string>
#include <vector>
#include <utility>

#include <ui_rqt_nodelet_assembler.h>

#include <QStringList>
#include <QString>
#include <QWidget>

#include <tinyxml.h>

namespace rqt_nodelet_assembler
{

class NodeletAssembler : public rqt_gui_cpp::Plugin
{
    Q_OBJECT

    //Methods
    public:
    NodeletAssembler();
    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
    virtual void shutdownPlugin();
    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

    protected:
    virtual QStringList getNodeletsFromPlugin(std::string plugin);
    virtual void updatePluginList();
    virtual void updateNodeletsList(std::string plugin);

    protected slots:
    virtual void onRefresh();
    virtual void onPluginChanged(int index);
    virtual void onNodeletChanged(int index);

    //Members
    protected:
    Ui::NodeletAssemblerWidget ui_;
    QWidget* widget_;

    private:
    TiXmlDocument current_plugin;
    ros::package::V_string nodelets_descriptions;
};
}//End namespace
#endif //_INCL_RQT_NODELET_ASSEMBLER_H_
