
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#include "nav-ling-1d-panel.h"

#include "styles.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QButtonGroup>
#include <QGroupBox>

USING_QSNS(ScignStage)

NAV_Ling1D_Panel::NAV_Ling1D_Panel(int vmn, int vmx, int v, QWidget* parent)
  :  QFrame(parent)
{
 main_layout_ = new QVBoxLayout;

 navigation_layout_ = new QHBoxLayout;

 filtered_up_button_ = new QPushButton(this);
 filtered_down_button_ = new QPushButton(this);

 sample_up_button_ = new QPushButton(this);
 sample_down_button_ = new QPushButton(this);

 sample_first_button_ = new QPushButton(this);
 auto_expand_button_ = new QPushButton("ON",this);

 filtered_up_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 filtered_down_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 sample_up_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 sample_down_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 sample_first_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Arrow-leftup-small.svg"));

 auto_expand_button_->setCheckable(true);
 auto_expand_button_->setChecked(true);

 auto_expand_button_->setStyleSheet(
   colorful_toggle_button_quiet_style_sheet_() + "QPushButton{max-width: 35px;}");

 auto_expand_button_->setToolTip("Set to OFF");

 connect(auto_expand_button_, &QPushButton::toggled,
   [this](bool b)
 {
  auto_expand_button_->setText(b?"ON":"OFF");
  auto_expand_button_->setToolTip(b?"Set to OFF":"Set to ON");
 });

 connect(auto_expand_button_, SIGNAL(toggled(bool)),
   this, SIGNAL(auto_expand_changed(bool)));


 peer_up_button_ = new QPushButton(this);
 peer_down_button_ = new QPushButton(this);

 peer_up_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 peer_down_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 connect(peer_up_button_, SIGNAL(clicked()),
   this, SIGNAL(peer_up_requested()));

 connect(peer_down_button_, SIGNAL(clicked()),
   this, SIGNAL(peer_down_requested()));

 connect(filtered_down_button_, SIGNAL(clicked()),
   this, SIGNAL(filtered_down_requested()));

 connect(filtered_up_button_, SIGNAL(clicked()),
   this, SIGNAL(filtered_up_requested()));

 section_start_button_ = new QPushButton(this);
 section_end_button_ = new QPushButton(this);

 section_start_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 section_end_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 connect(section_start_button_, SIGNAL(clicked()),
   this, SIGNAL(section_start_requested()));

 connect(section_end_button_, SIGNAL(clicked()),
   this, SIGNAL(section_end_requested()));




 section_up_button_ = new QPushButton(this);
 section_down_button_ = new QPushButton(this);

 section_up_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 section_down_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 connect(section_up_button_, SIGNAL(clicked()),
   this, SIGNAL(section_up_requested()));

 connect(section_down_button_, SIGNAL(clicked()),
   this, SIGNAL(section_down_requested()));



 connect(sample_up_button_, SIGNAL(clicked()),
   this, SIGNAL(sample_up_requested()));

 connect(sample_down_button_, SIGNAL(clicked()),
   this, SIGNAL(sample_down_requested()));

 connect(sample_first_button_, SIGNAL(clicked()),
   this, SIGNAL(sample_first_requested()));

 connect(auto_expand_button_, SIGNAL(clicked()),
   this, SIGNAL(sample_review_requested()));

 filter_up_down_layout_ = new QVBoxLayout;

 filter_up_down_layout_->addWidget(filtered_up_button_);
 filter_up_down_layout_->addWidget(filtered_down_button_);
 filter_up_down_layout_->addStretch();

 filter_up_down_group_box_ = new QGroupBox("Filtered Up/Down", this);
 filter_up_down_button_group_ = new QButtonGroup(this);

 filter_up_down_button_group_->addButton(filtered_up_button_);
 filter_up_down_button_group_->addButton(filtered_down_button_);

 filter_up_down_group_box_->setLayout(filter_up_down_layout_);

 navigation_layout_->addWidget(filter_up_down_group_box_);

 example_up_down_layout_ = new QVBoxLayout;

 example_up_down_layout_->addWidget(sample_up_button_);
 example_up_down_layout_->addWidget(sample_down_button_);
 example_up_down_layout_->addStretch();

 example_up_down_group_box_ = new QGroupBox("Examples Up/Down", this);
 example_up_down_button_group_ = new QButtonGroup(this);

 example_up_down_button_group_->addButton(sample_up_button_);
 example_up_down_button_group_->addButton(sample_down_button_);

 example_up_down_group_box_->setLayout(example_up_down_layout_);

 navigation_layout_->addWidget(example_up_down_group_box_);

 peer_up_down_layout_ = new QVBoxLayout;

 peer_up_down_layout_->addWidget(peer_up_button_);
 peer_up_down_layout_->addWidget(peer_down_button_);
 peer_up_down_layout_->addStretch();

 peer_up_down_group_box_ = new QGroupBox("Peer Up/Down", this);
 peer_up_down_button_group_ = new QButtonGroup(this);


 peer_up_down_button_group_->addButton(peer_up_button_);
 peer_up_down_button_group_->addButton(peer_down_button_);

 peer_up_down_group_box_->setLayout(peer_up_down_layout_);

 navigation_layout_->addWidget(peer_up_down_group_box_);


 section_se_layout_ = new QVBoxLayout;

 section_se_layout_->addWidget(section_start_button_);
 section_se_layout_->addWidget(section_end_button_);
 section_se_layout_->addStretch();

 section_se_group_box_ = new QGroupBox("Section Start/End", this);
 section_se_button_group_ = new QButtonGroup(this);


 section_se_button_group_->addButton(section_start_button_);
 section_se_button_group_->addButton(section_end_button_);

 section_se_group_box_->setLayout(section_se_layout_);

 navigation_layout_->addWidget(section_se_group_box_);



 section_up_down_layout_ = new QVBoxLayout;

 section_up_down_layout_->addWidget(section_up_button_);
 section_up_down_layout_->addWidget(section_down_button_);
 section_up_down_layout_->addStretch();

 section_up_down_group_box_ = new QGroupBox("Section Up/Down", this);
 section_up_down_button_group_ = new QButtonGroup(this);


 section_up_down_button_group_->addButton(section_up_button_);
 section_up_down_button_group_->addButton(section_down_button_);

 section_up_down_group_box_->setLayout(section_up_down_layout_);

 navigation_layout_->addWidget(section_up_down_group_box_);



 //first_auto_expand_note_layout_ = new QVBoxLayout;
 first_auto_expand_layout_ = new QVBoxLayout;

 first_layout_ = new QHBoxLayout;
 first_label_ = new QLabel("First", this);
 //first_layout_->addStretch();
 //sample_first_button_->setText("First");
 first_layout_->addWidget(first_label_);
 first_layout_->addWidget(sample_first_button_);
 first_layout_->addStretch();

 //first_auto_expand_layout_->addStretch();
 first_auto_expand_layout_->addLayout(first_layout_);
 first_auto_expand_layout_->addStretch();

 auto_expand_layout_ = new QVBoxLayout;
 auto_expand_label_ = new QLabel("Auto Expand", this);
 auto_expand_layout_->addStretch();
 auto_expand_layout_->addWidget(auto_expand_label_);
 auto_expand_layout_->addWidget(auto_expand_button_);
 auto_expand_layout_->addStretch();

 first_auto_expand_layout_->addLayout(auto_expand_layout_);
 first_auto_expand_layout_->addStretch();

 //first_auto_expand_note_layout_->addLayout(first_auto_expand_layout_);

// first_auto_expand_label_ = new QLabel("Note: Scroll via \"Peer\" to highlight "
//   "variations in each group.", this);
// first_auto_expand_note_layout_->addWidget(first_auto_expand_label_);

 navigation_layout_->addStretch();
 navigation_layout_->addLayout(first_auto_expand_layout_);
 navigation_layout_->addStretch();

 //navigation_layout_->addLayout(zoom_sample_distractor_layout_);

 navigation_layout_->addStretch();


 main_layout_->addLayout(navigation_layout_);

 setLayout(main_layout_);
}

NAV_Ling1D_Panel::~NAV_Ling1D_Panel()
{

}

void NAV_Ling1D_Panel::set_sample_text(int r)
{
 //sample_line_edit_->setText(QString::number(r));
}
