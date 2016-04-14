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
#include <QInputDialog>
#include <boost/filesystem.hpp>

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
        ui_.name_f->setText("Nodelet");
        ui_.description_f->setText("Description");
        connect(ui_.plugin_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onPluginChanged(int)));
        ui_.refresh_push_button->setIcon(QIcon::fromTheme("view-refresh"));
        connect(ui_.refresh_push_button, SIGNAL(pressed()), this, SLOT(onRefresh()));
        connect(ui_.nodelet_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onNodeletChanged(int)));
        connect(ui_.add_manager_push_button, SIGNAL(pressed()), this, SLOT(onAddManager()));
        connect(ui_.add_nodelet_push_button, SIGNAL(pressed()), this, SLOT(onAddNodelet()));
        connect(ui_.remove_push_button, SIGNAL(pressed()), this, SLOT(onRemoveNodelet()));
        connect(ui_.clear_push_button, SIGNAL(pressed()), this, SLOT(onClear()));
        connect(ui_.write_launch_push_button, SIGNAL(pressed()), this, SLOT(onWriteLaunch()));
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
    NodeletAssembler::getNodeletsFromPlugin(std::string plugin)
    {
        QStringList nodelets;
        nodelets_descriptions.clear();
        TiXmlDocument doc_plugin;
        if (doc_plugin.LoadFile(plugin)){
            TiXmlHandle handle(&doc_plugin);
            TiXmlElement* pLibTag = handle.FirstChild("library").ToElement();
            for (pLibTag; pLibTag; pLibTag=pLibTag->NextSiblingElement())
            {
                TiXmlElement* pTag = pLibTag->FirstChild("class")->ToElement();
                for (pTag; pTag; pTag=pTag->NextSiblingElement())
                {
                    std::string desc = pTag->FirstChild("description")->ToElement()->GetText();
                    nodelets_descriptions.push_back(desc);
                    nodelets.append( pTag->Attribute("name") );
                }
            }
        }
        return nodelets;
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
    NodeletAssembler::updateNodeletsList(std::string plugin)
    {
        ui_.nodelet_combo_box->clear();
        QStringList nlist = getNodeletsFromPlugin(plugin);
        ui_.nodelet_combo_box->insertItems(0, nlist);
    }

    void
    NodeletAssembler::onRefresh()
    {
        updatePluginList();
        ui_.nodelet_frame->setDisabled(true);
        ui_.name_f->setText("Nodelet");
        ui_.description_f->setText("Description");
    }

    void
    NodeletAssembler::onAddManager()
    {
        bool ok;
        QString name = QInputDialog::getText(widget_, tr("QInputDialog::getText()"),
                                         tr("Manager Name:"), QLineEdit::Normal,
                                         "nodelet_manager", &ok);
        if (!ok || name.isEmpty())
            return;

    }

    void
    NodeletAssembler::onPluginChanged(int index)
    {
        if (index == -1)
            return;
        std::string plugin_path = ui_.plugin_combo_box->itemText(index).toStdString();
        boost::filesystem::path pp(plugin_path);
        if (boost::filesystem::exists(pp) && boost::filesystem::is_regular_file(pp))
            updateNodeletsList(plugin_path);
    }

    void
    NodeletAssembler::onNodeletChanged(int index)
    {
        if (index == -1)
            return;
        ui_.nodelet_frame->setDisabled(false);
        std::string name = ui_.nodelet_combo_box->itemText(index).toStdString();
        ui_.name_f->setText(name.c_str());
        ui_.description_f->setText(nodelets_descriptions[index].c_str());
    }

    void
    NodeletAssembler::onAddNodelet()
    {
        //TODO
    }

    void
    NodeletAssembler::onRemoveNodelet()
    {
        //TODO
    }

    void
    NodeletAssembler::onClear()
    {
        //TODO
    }

    void
    NodeletAssembler::onWriteLaunch()
    {
        //TODO
    }
}//End namespace

PLUGINLIB_EXPORT_CLASS(rqt_nodelet_assembler::NodeletAssembler, rqt_gui_cpp::Plugin)
