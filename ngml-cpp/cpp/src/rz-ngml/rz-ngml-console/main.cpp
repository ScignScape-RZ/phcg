
#include "rz-ngml/kernel/document/rz-ngml-document.h"

#include "rz-ngml/output/rz-ngml-output-html.h"
#include "rz-ngml/output/rz-ngml-output-latex.h"
#include "rz-ngml/output/rz-ngml-output-khif.h"

#include "rz-ngml/output/rz-ngml-output-xml.h"

#include "rz-ngml/kernel/document/rz-ngml-folder.h"

#include "rzns.h"

#include <QRegularExpression>

// //
//#include <QDomDocument>
//#include <QDomElement>
//#include <QDomNode>


USING_RZNS(NGML)

#define DEFAULT_DIRECTORY "../.."

#include <QApplication>
#include <QFileDialog>
#include <QDebug>


int main(int argc, char* argv[])
{
 QApplication qapp(argc, argv);

 QString folder = QFileDialog::getExistingDirectory(nullptr,
   "Select Folder"
   " (needs /ngml subfolder)",
   DEFAULT_DIRECTORY);

 NGML_Folder ngf(folder + "/ngml");
 ngf.convert_all_files(folder, folder + "/khif");

}


