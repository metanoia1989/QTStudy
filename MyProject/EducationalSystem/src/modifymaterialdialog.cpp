#include "modifymaterialdialog.h"
#include "ui_modifymaterialdialog.h"

ModifyMaterialDialog::ModifyMaterialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyMaterialDialog)
{
    ui->setupUi(this);

    // 设置按钮组
    techGroup = new QButtonGroup(this);
    techGroup->addButton(ui->radioTechNo, 0);
    techGroup->addButton(ui->radioTechYes, 1);


    paperGroup = new QButtonGroup(this);
    paperGroup->addButton(ui->radioPaperNo, 0);
    paperGroup->addButton(ui->radioPaperYes, 1);
    paperGroup->addButton(ui->radioPaperSubmit, 2);

    photoGroup = new QButtonGroup(this);
    photoGroup->addButton(ui->radioPhotoNo, 0);
    photoGroup->addButton(ui->radioPhotoYes, 1);

    educationGroup = new QButtonGroup(this);
    educationGroup->addButton(ui->radioEducationNo, 0);
    educationGroup->addButton(ui->radioEducationYes, 1);

    idCardGroup = new QButtonGroup(this);
    idCardGroup->addButton(ui->radioIdCardNo, 0);
    idCardGroup->addButton(ui->radioIdCardYes, 1);

    workGroup = new QButtonGroup(this);
    workGroup->addButton(ui->radioWorkNo, 0);
    workGroup->addButton(ui->radioWorkYes, 1);

    socialGroup = new QButtonGroup(this);
    socialGroup->addButton(ui->radioSocialNo, 0);
    socialGroup->addButton(ui->radioSocialYes, 1);

    certGroup = new QButtonGroup(this);
    certGroup->addButton(ui->radioCertNo, 0);
    certGroup->addButton(ui->radioCertYes, 1);
    certGroup->addButton(ui->radioCertSend, 2);
}

ModifyMaterialDialog::~ModifyMaterialDialog()
{
    delete ui;
}

QMap<QString, int> ModifyMaterialDialog::getResults()
{
    QMap<QString, int> results;
    int id = -1;
    if ((id = techGroup->checkedId()) != -1) {
        results["data_sent"] = id;
    }
    if ((id = paperGroup->checkedId()) != -1) {
        results["paper_photo"] = id;
    }
    if ((id = photoGroup->checkedId()) != -1) {
        results["electronic_photo"] = id;
    }
    if ((id = educationGroup->checkedId()) != -1) {
        results["education"] = id;
    }
    if ((id = idCardGroup->checkedId()) != -1) {
        results["sfzfyj"] = id;
    }
    if ((id = workGroup->checkedId()) != -1) {
        results["work_proof"] = id;
    }
    if ((id = socialGroup->checkedId()) != -1) {
        results["social_data"] = id;
    }
    if ((id = certGroup->checkedId()) != -1) {
        results["graduation_status"] = id;
    }

    return results;
}

/**
 * 清除单选的选中状态
 */
void ModifyMaterialDialog::clearChecked()
{
    QList<QButtonGroup*> groups = {
        techGroup,
        paperGroup,
        photoGroup,
        educationGroup,
        idCardGroup,
        workGroup,
        socialGroup,
        certGroup
    };
    for (int i = 0; i < groups.size(); i++) {
        QButtonGroup *group = groups.at(i);
        QAbstractButton *checked = group->checkedButton();
        if (checked) {
            group->setExclusive(false);
            checked->setChecked(false);
            group->setExclusive(true);
        }
    }
}
