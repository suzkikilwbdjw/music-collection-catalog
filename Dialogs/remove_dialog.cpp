#include "remove_dialog.h"
#include <QMessageBox>
#include "ui_remove_dialog.h"

RemoveDialog::RemoveDialog(Database *db, TableType tableType, int id, QWidget *parent)
    : QDialog(parent)
    , _db(db)
    , _tableType(tableType)
    , _id(id)
    , ui(new Ui::RemoveDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &RemoveDialog::on_buttonBox_accepted);
}

RemoveDialog::~RemoveDialog()
{
    delete ui;
}

void RemoveDialog::on_buttonBox_accepted()
{
    try {
        switch (_tableType) {
        case TableType::artists:
            _db->getArtists()->remove(_id);
            _db->getArtistsModel()->select();
            break;
        case TableType::countries:
            _db->getCountries()->remove(_id);
            _db->getCountriesModel()->select();
            break;
        case TableType::labels:
            _db->getLabels()->remove(_id);
            _db->getLabelsModel()->select();
            break;
        case TableType::albums:
            _db->getAlbums()->remove(_id);
            _db->getAlbumsModel()->select();
            break;
        case TableType::songs:
            _db->getSongs()->remove(_id);
            _db->getSongsModel()->select();
            break;
        case TableType::genres:
            _db->getGenres()->remove(_id);
            _db->getGenresModel()->select();
            break;
        default:
            break;
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}
