#include "patientdatabase.h"

PatientDataBase::PatientDataBase(QObject *parent ): QObject(parent)
{
    getPatientsListFromJson();
    webView = new QWebEngineView();

    connect(webView, &QWebEngineView::loadFinished, &loop, &QEventLoop::quit);
    connect(webView->page(), &QWebEnginePage::pdfPrintingFinished, &loop, &QEventLoop::quit);
}

PatientDataBase::~PatientDataBase()
{
    delete webView;
}

/**
 * @brief  Добавляет нового пациента в БД
 * @param fullName
 * @param age
 * @param sex
 * @param birthDate
 * @param address
 * @param phoneNumber
 * @param occupation
 */
void PatientDataBase::addNewPatient(QString fullName, int age, bool sex,
                                    QString birthDate, QString address,
                                    QString phoneNumber, QString occupation)
{
    if (patientsList == nullptr){
        patientsList = new QList<Patient>;
    }
    else {
        if (isProfileExists(birthDate) == true) {
            qDebug() << "[PatienDataBase::addNewPatient()] - Patient " << fullName << " already exists. Selecting this profile...\n";
            return;
        }
    }

    Patient newPatient;

    newPatient.fullName = fullName;
    newPatient.age = age;
    newPatient.sex = sex;
    newPatient.birthDate = birthDate;
    newPatient.address = address;
    newPatient.phoneNumber = phoneNumber;
    newPatient.occupation = occupation;

    patientsList->append(newPatient);

    qDebug() << "[PatientDataBase::addNewPatient()] - Saving new profile...\n";
    saveProfileToJson(newPatient);
}

/**
 * @brief Добавляет новую запись в амбулаторную карту пациента
 * @param birthDate
 * @param recordDate
 * @param anamnesis
 * @param complaints
 * @param diseases
 * @param diagnosis
 * @param treatment
 * @return Успешно ли добавлена запись
 */
bool PatientDataBase::addNewRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints,
                                   QString diseases, QString diagnosis, QString treatment, QString treatmentResult)
{
    for (auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            if (p.cardRecords.isEmpty())
            {
                Record_t newRecord;

                newRecord.date = recordDate;
                newRecord.currentDiagnosis = diagnosis;
                newRecord.anamnesis = anamnesis;
                newRecord.complaints = complaints;
                newRecord.diseases = diseases;
                newRecord.treatment = treatment;
                newRecord.treatmentResult = treatmentResult;

                p.cardRecords.append(newRecord);

                return true;
            }
            else
            {
                // Проверяем список на наличие записи по указанной дате
                for (const auto &r : p.cardRecords)
                {
                    if (r.date == recordDate)
                        return false;
                }

                Record_t newRecord;

                newRecord.date = recordDate;
                newRecord.currentDiagnosis = diagnosis;
                newRecord.anamnesis = anamnesis;
                newRecord.complaints = complaints;
                newRecord.diseases = diseases;
                newRecord.treatment = treatment;
                newRecord.treatmentResult = treatmentResult;

                p.cardRecords.append(newRecord);

                return true;
            }
        }
    }
    return false;
}

void PatientDataBase::reloadDatabase()
{
    getPatientsListFromJson();
}

/**
 * @brief Обновляет данные БД пациентов в patients.json
 */
void PatientDataBase::updateDbToFile()
{
    QJsonDocument jsonDocument;

    QJsonArray jsonArray = jsonDocument.array();

    foreach (Patient p, *patientsList)
    {
        QJsonObject PatientProfileObj;

        PatientProfileObj.insert("fullname", p.fullName);
        PatientProfileObj.insert("age", p.age);
        PatientProfileObj.insert("sex", p.sex);
        PatientProfileObj.insert("birthdate", p.birthDate);
        PatientProfileObj.insert("address", p.address);
        PatientProfileObj.insert("phoneNumber", p.phoneNumber);
        PatientProfileObj.insert("occupation", p.occupation);
        PatientProfileObj.insert("records", convertRecordsToJsonArray(p.cardRecords));

        jsonArray.append(PatientProfileObj);
    }

    jsonDocument.setArray(jsonArray);

    QFileInfo fInfo(JSON_PATIENT_FILE_PATH);
    QFile jsonFile(JSON_PATIENT_FILE_PATH);

    if (fInfo.exists() == true)
    {
       jsonFile.remove();
       jsonFile.open(QFile::WriteOnly);
       jsonFile.write(jsonDocument.toJson());
       jsonFile.close();
    }

    qDebug() << "[PatienDataBase::updateDbToFile()] - Database updated\n";
}

/**
 * @brief Обновляет запись пациента
 * @param birthDate
 * @param recordDate
 * @param anamnesis
 * @param complaints
 * @param diseases
 * @param diagnosis
 * @param treatment
 */
void PatientDataBase::updateRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints,
                                   QString diseases, QString diagnosis, QString treatment, QString treatmentResult)
{
    for (auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                {
                    r.anamnesis = anamnesis;
                    r.complaints = complaints;
                    r.currentDiagnosis = diagnosis;
                    r.diseases = diseases;
                    r.treatment = treatment;
                    r.treatmentResult = treatmentResult;
                    break;
                }
            }
        }
    }
}

void PatientDataBase::deleteRecord(QString birthDate, QString recordDate)
{
    for (auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (int i = 0; i < p.cardRecords.size(); i++)
            {
                if (p.cardRecords[i].date == recordDate)
                    p.cardRecords.removeAt(i);
            }
        }
    }
}

/**
 * @brief Удаляет пациента из БД по указанному параметру
 * @param birthDate
 * @return true, если удаление прошло успешно
 */
bool PatientDataBase::deletePatient(QString birthDate)
{
    int i = 0;

    if (patientsList->isEmpty() == true)
        return false;

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
        {
            patientsList->removeAt(i);
            return true;
        }
        else
            i++;

    }
    return false;
}

void PatientDataBase::setCurrentDoctorInitials(QString initials)
{
    currentDoctorInitials = initials;
}

QString PatientDataBase::getFullName(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.fullName;
    }
    return "";
}

bool PatientDataBase::getSex(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return false;

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.sex == Patient::SexType::MAN ? Patient::SexType::MAN : Patient::SexType::WOMAN;
    }
    return false;
}

QString PatientDataBase::getBirthDate(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

        foreach(Patient patient, *patientsList)
        {
            if (patient.birthDate == birthDate)
                return patient.birthDate;
        }
    return "";
}

QString PatientDataBase::getAddress(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.address;
    }
    return "";
}

QString PatientDataBase::getOccupation(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.occupation;
    }
    return "";
}

QStringList PatientDataBase::getRecordsList(QString birthDate)
{
    QStringList list;

    if (patientsList->isEmpty() == true)
        return QStringList();

    for (const auto &patient : *patientsList)
    {
        if (patient.birthDate == birthDate)
        {
            for (const auto &record : patient.cardRecords)
                list.append(record.date);
            return list;
        }
    }
    return QStringList();
}

QString PatientDataBase::getAnamnesis(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.anamnesis;
            }
        }
    }
    return "";
}

QString PatientDataBase::getComplaints(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.complaints;
            }
        }
    }
    return "";
}

QString PatientDataBase::getDiagnosis(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.currentDiagnosis;
                }
            }
        }
    return "";
}

QString PatientDataBase::getDiseases(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.diseases;
            }
        }
    }
    return "";
}

QString PatientDataBase::getTreatment(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.treatment;
            }
        }
    }
    return "";
}

QString PatientDataBase::getTreatmentResult(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.treatmentResult;
            }
        }
    }
    return "";
}

void PatientDataBase::saveCardPdf(QString birthDate)
{
    QString fileName;
    QString patientName;

    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            // Для подстановки ФИО в карту
            patientName = p.fullName;

            fileName = p.fullName + p.birthDate;
            fileName.remove(' ');
            fileName.replace('.', '_');
            break;
        }
    }

    QString path = QFileDialog::getSaveFileName(nullptr, "Сохранить в PDF", fileName + ".pdf", "PDF (*.pdf)");

    generateFullCard(birthDate, path);
}

void PatientDataBase::saveCardPdf(QString birthDate, int pageNumber, bool fillPatientData)
{
    QString fileName;
    QString patientName;

    if (fillPatientData == true)
    {
        for (const auto &p : *patientsList)
        {
            if (p.birthDate == birthDate)
            {
                // Для подстановки ФИО в карту
                patientName = p.fullName;

                fileName = p.fullName + p.birthDate;
                fileName.remove(' ');
                fileName.replace('.', '_');
                break;
            }
        }

        switch(pageNumber)
        {
        case 1: // Обложка
            fileName.append("_обложка");
            break;
        case 2: // Данные осмотра полости рта
            fileName.append("_данные_полости_рта");
            break;
        case 3: // Страница дневника
            fileName.append("_лечение");
            break;
        case 4: // Страница лечения
            fileName.append("_дневник");
            break;
        case 5: // Страница плана
            fileName.append("_план");
            break;
        }
    }
    else
    {
        switch(pageNumber)
        {
        case 1: // Обложка
            fileName.append("МедКарта_обложка");
            break;
        case 2: // Данные осмотра полости рта
            fileName.append("МедКарта_данные_полости_рта");
            break;
        case 3: // Страница дневника
            fileName.append("МедКарта_лечение");
            break;
        case 4: // Страница лечения
            fileName.append("МедКарта_дневник");
            break;
        case 5: // Страница плана
            fileName.append("МедКарта_план");
            break;
        }
    }

    QString path = QFileDialog::getSaveFileName(nullptr, "Сохранить в PDF", fileName + ".pdf", "PDF (*.pdf)");
    generatePage(birthDate, path, pageNumber, fillPatientData);
}

void PatientDataBase::saveDiaryPdf(QString birthDate, QString recordDate)
{
    QString fileName;
    QString patientName;
    Record_t currentRecord;

    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            // Для подстановки ФИО в карту
            patientName = p.fullName;

            fileName = p.fullName + p.birthDate;
            fileName.remove(' ');
            fileName.replace('.', '_');

            for (const auto &recIt : p.cardRecords)
            {
                if (recIt.date == recordDate)
                {
                    currentRecord = recIt;
                    break;
                }
            }
        }
    }

    QString path = QFileDialog::getSaveFileName(nullptr, "Сохранить в PDF", fileName + ".pdf", "PDF (*.pdf)");
    generateDiary(currentRecord, path);
}

int PatientDataBase::getAge(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return 0;

        foreach(Patient patient, *patientsList)
        {
            if (patient.birthDate == birthDate)
                return patient.age;
        }
    return 0;
}

QString PatientDataBase::getPhoneNumber(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.phoneNumber;
    }
    return "";
}

/**
 * @brief Получает список пациентов из JSON файла
 */
void PatientDataBase::getPatientsListFromJson()
{
    QJsonDocument doc = loadJson();

    if (patientsList == nullptr)
        patientsList = new QList<Patient>;

    Patient currentProfile;

    QJsonArray array = doc.array();

    QJsonObject currentObj;

    if (array.isEmpty() == true)
        return;

    if (patientsList->isEmpty() == false)
        patientsList->clear();

    foreach(const QJsonValue &v, array)
    {
        currentObj = v.toObject();

        currentProfile.fullName = currentObj["fullname"].toString();
        currentProfile.age = currentObj["age"].toInt();
        currentProfile.sex = currentObj["sex"].toBool();
        currentProfile.birthDate = currentObj["birthdate"].toString();
        currentProfile.address = currentObj["address"].toString();
        currentProfile.birthDate = currentObj["birthdate"].toString();
        currentProfile.phoneNumber = currentObj["phoneNumber"].toString();
        currentProfile.occupation = currentObj["occupation"].toString();

        currentProfile.cardRecords = convertJsonRecordsToList(currentObj["records"].toArray());

        patientsList->append(currentProfile);
    }

    // Сортировка по фамилии
    std::sort(patientsList->begin(), patientsList->end(), [](const Patient &left, const Patient &right)
    {
        return left.fullName.compare(right.fullName) < 0 ? true : false;
    });
}

/**
 * @brief Заполнение строк с лечением
 * @param recIt
 * @param html
 */
void PatientDataBase::fillTreatment(Record_t recIt, QString *html)
{
    QString treatment = recIt.treatment;
    QString array[5]; // Массив для поля "Лечение"

    // Если строка больше размера первой строки, то делаем разметку спец. символами и распределяем строки в массив
    // FIXME: Первые две строки на 92 и 113 символа размечаются корректно, но потом разметка идёт на 114-ом символе
    if (treatment.length() <= CARD_FIRST_FIELD_CHAR_COUNT + 29)
    {
        array[0] = treatment;
        array[1] = ".";
        array[2] = ".";
        array[3] = ".";
        array[4] = ".";
    }
    else
    {
        // Расставляем спец. символы со следующего символа строки
        int counter = 0;
        treatment.insert(CARD_FIRST_FIELD_CHAR_COUNT + 29 , '$');

        for (int i = CARD_FIRST_FIELD_CHAR_COUNT + 1 ; i < treatment.length(); i++)
        {
            counter++;
            if (counter == CARD_FIELD_CHAR_COUNT + 47)
            {
                counter = 0;
                treatment.insert(i, '$');
            }
        }

        // Заполняем элемент массива, пока не дошли до спец. символа
        for (int i = 0; i < 5; i++)
        {
            int counter = 0;
            QString chars;

            for (auto &c : treatment)
            {
                chars += c;
                if (c == "$")
                {
                    array[i] = chars;
                    treatment.remove(0, chars.length());
                    break;
                }
            }
        }

        // Проверяем, остались ли ещё символы и заполняем остаток в пустой элемент массива
        if (treatment.isEmpty() == false)
        {
            for (auto &it : array)
            {
                if (it.isEmpty())
                {
                    it = treatment;
                    break;
                }
            }
        }
    }
    // Проверяем наличие в массиве спец. символе а также его пустоту для замены иным символом, чтобы не слетела вёрстка
    for (auto &it : array)
    {
        it.remove("$");
        if (it == "")
            it = ".";
    }

    html->replace("МЕТКА_ЛЕЧЕНИЕ1", array[0]);
    html->replace("МЕТКА_ЛЕЧЕНИЕ2", array[1]);
    html->replace("МЕТКА_ЛЕЧЕНИЕ3", array[2]);
    html->replace("МЕТКА_ЛЕЧЕНИЕ4", array[3]);
    html->replace("МЕТКА_ЛЕЧЕНИЕ5", array[4]);
}

/**
 * @brief Заполнение строк с результатами лечения
 * @param recIt
 * @param html
 */
void PatientDataBase::fillTreatmentResult(Record_t recIt, QString *html)
{
    QString treatmentResult = recIt.treatmentResult;
    QString array[5]; // Массив для поля "Результаты лечения (эпикриз)"

    // Если строка больше размера первой строки, то делаем разметку спец. символами и распределяем строки в массив
    // FIXME: Первые две строки на 92 и 113 символа размечаются корректно, но потом разметка идёт на 114-ом символе
    if (treatmentResult.length() <= CARD_FIRST_FIELD_CHAR_COUNT)
    {
        array[0] = treatmentResult;
        array[1] = ".";
        array[2] = ".";
        array[3] = ".";
        array[4] = ".";
    }
    else
    {
        // Расставляем спец. символы со следующего символа строки
        int counter = 0;
        treatmentResult.insert(CARD_FIRST_FIELD_CHAR_COUNT , '$');

        for (int i = CARD_FIRST_FIELD_CHAR_COUNT + 1 ; i < treatmentResult.length(); i++)
        {
            counter++;
            if (counter == CARD_FIELD_CHAR_COUNT)
            {
                counter = 0;
                treatmentResult.insert(i, '$');
            }
        }

        // Заполняем элемент массива, пока не дошли до спец. символа
        for (int i = 0; i < 5; i++)
        {
            int counter = 0;
            QString chars;

            for (auto &c : treatmentResult)
            {
                chars += c;
                if (c == "$")
                {
                    array[i] = chars;
                    treatmentResult.remove(0, chars.length());
                    break;
                }
            }
        }

        // Проверяем, остались ли ещё символы и заполняем остаток в пустой элемент массива
        if (treatmentResult.isEmpty() == false)
        {
            for (auto &it : array)
            {
                if (it.isEmpty())
                {
                    it = treatmentResult;
                    break;
                }
            }
        }
    }
    // Проверяем наличие в массиве спец. символе а также его пустоту для замены иным символом, чтобы не слетела вёрстка
    for (auto &it : array)
    {
        it.remove("$");
        if (it == "")
            it = ".";
    }

    html->replace("МЕТКА_ЭПИКРИЗ1", array[0]);
    html->replace("МЕТКА_ЭПИКРИЗ2", array[1]);
    html->replace("МЕТКА_ЭПИКРИЗ3", array[2]);
    html->replace("МЕТКА_ЭПИКРИЗ4", array[3]);
    html->replace("МЕТКА_ЭПИКРИЗ5", array[4]);
}

/**
 * @brief Заполнение строк объективного исследования, внешнего осмотра
 * @todo Количество добавляемых символов ограниченно. Исправить!
 * @param recIt
 * @param html
 */
void PatientDataBase::fillExternalInspection(Record_t recIt, QString *html)
{
    QString inspection = recIt.diseases;
    QString array[5]; // Массив для поля "Внешний осмотр"
    QString array2[7]; // Массив для поля "Объективный осмотр"

    // Если строка больше размера первой строки, то делаем разметку спец. символами и распределяем строки в массив
    // FIXME: Первые две строки на 92 и 113 символа размечаются корректно, но потом разметка идёт на 114-ом символе
    if (inspection.length() <= CARD_FIRST_FIELD_CHAR_COUNT)
    {
        array[0] = inspection;
        array[1] = ".";
        array[2] = ".";
        array[3] = ".";
        array[4] = ".";
    }
    else
    {
        // Расставляем спец. символы со следующего символа строки
        int counter = 0;
        inspection.insert(CARD_FIRST_FIELD_CHAR_COUNT , '$');

        for (int i = CARD_FIRST_FIELD_CHAR_COUNT + 1 ; i < inspection.length(); i++)
        {
            counter++;
            if (counter == CARD_FIELD_CHAR_COUNT)
            {
                counter = 0;
                inspection.insert(i, '$');
            }
        }

        // Заполняем элемент массива, пока не дошли до спец. символа
        for (int i = 0; i < 5; i++)
        {
            int counter = 0;
            QString chars;

            for (auto &c : inspection)
            {
                chars += c;
                if (c == "$")
                {
                    array[i] = chars;
                    inspection.remove(0, chars.length());
                    break;
                }
            }
        }

        // Проверяем, остались ли ещё символы и заполняем остаток в пустой элемент массива
        if (inspection.isEmpty() == false)
        {
            for (auto &it : array)
            {
                if (it.isEmpty())
                {
                    it = inspection;
                    break;
                }
            }
        }
    }
    // Проверяем наличие в массиве спец. символе а также его пустоту для замены иным символом, чтобы не слетела вёрстка
    for (auto &it : array)
    {
        it.remove("$");
        if (it == "")
            it = ".";
    }

    html->replace("МЕТКА_ОСМОТР1", array[0]);
    html->replace("МЕТКА_ОСМОТР2", array[1]);
    html->replace("МЕТКА_ОСМОТР3", array[2]);
    html->replace("МЕТКА_ОСМОТР4", array[3]);
    html->replace("МЕТКА_ОСМОТР5", array[4]);

    html->replace("МЕТКА_ОБЪЕКТИВНО1", ".");
    html->replace("МЕТКА_ОБЪЕКТИВНО2", ".");
    html->replace("МЕТКА_ОБЪЕКТИВНО3", ".");
    html->replace("МЕТКА_ОБЪЕКТИВНО4", ".");
    html->replace("МЕТКА_ОБЪЕКТИВНО5", ".");
    html->replace("МЕТКА_ОБЪЕКТИВНО6", ".");
    html->replace("МЕТКА_ОБЪЕКТИВНО7", ".");
}

/**
 * @brief Заполнение строк с анамнезом дневника мед. карты
 * @todo Количество добавляемых символов ограниченно. Исправить!
 * @param recIt
 * @param html
 */
void PatientDataBase::fillAnamnesis(Record_t recIt, QString *html)
{
    if (recIt.anamnesis.length() <= 101)
    {
        if (recIt.anamnesis.length() <= 10)
            html->replace("МЕТКА_АНАМНЕЗ1", ".");
        else
            html->replace("МЕТКА_АНАМНЕЗ1", recIt.anamnesis);

        html->replace("МЕТКА_АНАМНЕЗ2", ".");
    }
    else
    {
        QString buffer, anamnesis = recIt.anamnesis;

        for (int i = 0; i < 101; i++)
        {
            buffer.append(anamnesis.at(i));
        }
        anamnesis.remove(0, 101);

        html->replace("МЕТКА_АНАМНЕЗ2", buffer);
    }
}

/**
 * @brief Заполнение строк с жалобами дневника мед. карты
 * @todo Количество добавляемых символов ограниченно. Исправить!
 * @param recIt
 * @param html
 */
void PatientDataBase::fillComplaints(Record_t recIt, QString *html)
{
    QString complaints = recIt.complaints;
    QString array[5]; // Массив для поля "Жалобы"

    // Если строка больше размера первой строки, то делаем разметку спец. символами и распределяем строки в массив
    // FIXME: Первые две строки на 92 и 113 символа размечаются корректно, но потом разметка идёт на 114-ом символе
    if (complaints.length() <= CARD_FIRST_FIELD_CHAR_COUNT + 9)
    {
        array[0] = complaints;
        array[1] = ".";
        array[2] = ".";
        array[3] = ".";
        array[4] = ".";
    }
    else
    {
        // Расставляем спец. символы со следующего символа строки
        int counter = 0;
        complaints.insert(CARD_FIRST_FIELD_CHAR_COUNT + 9, '$');

        for (int i = CARD_FIRST_FIELD_CHAR_COUNT + 1 ; i < complaints.length(); i++)
        {
            counter++;
            if (counter == CARD_FIELD_CHAR_COUNT + 47)
            {
                counter = 0;
                complaints.insert(i, '$');
            }
        }

        // Заполняем элемент массива, пока не дошли до спец. символа
        for (int i = 0; i < 5; i++)
        {
            int counter = 0;
            QString chars;

            for (auto &c : complaints)
            {
                chars += c;
                if (c == "$")
                {
                    array[i] = chars;
                    complaints.remove(0, chars.length());
                    break;
                }
            }
        }

        // Проверяем, остались ли ещё символы и заполняем остаток в пустой элемент массива
        if (complaints.isEmpty() == false)
        {
            for (auto &it : array)
            {
                if (it.isEmpty())
                {
                    it = complaints;
                    break;
                }
            }
        }
    }
    // Проверяем наличие в массиве спец. символе а также его пустоту для замены иным символом, чтобы не слетела вёрстка
    for (auto &it : array)
    {
        it.remove("$");
        if (it == "")
            it = ".";
    }

    html->replace("МЕТКА_ЖАЛОБЫ1", array[0]);
    html->replace("МЕТКА_ЖАЛОБЫ2", array[1]);
    html->replace("МЕТКА_ЖАЛОБЫ3", array[2]);
    html->replace("МЕТКА_ЖАЛОБЫ4", array[3]);
    html->replace("МЕТКА_ЖАЛОБЫ5", array[4]);
}

// FIXME: Вынести в отдельный поток
void PatientDataBase::generatePage(QString birthDate, QString path, int pageNumber, bool fillPatientData)
{
    if (fillPatientData == true)
    {
        QString patientName;
        QString sex;
        QString age;
        QString address;
        QString occupation;

        for (const auto &p : *patientsList)
        {
            if (p.birthDate == birthDate)
            {
                // Для подстановки ФИО в карту
                patientName = p.fullName;
                sex = p.sex == false ? "М" : "Ж";
                age = QString::number(p.age);
                address = p.address;
                occupation = p.occupation;
                break;
            }
        }
    }
    else
    {
        QString pageName;
        pageName.append("page");
        pageName.append(QString::number(pageNumber));
        pageName.append(".html");

        QString pageFile = "://cards_src/";
        pageFile.append(pageName);

        QFile file(pageFile);
        file.open(QIODevice::ReadOnly);

        QTextStream input(&file);
        input.setCodec( "utf-8" );
        QString html = input.readAll();
        file.close();

        switch(pageNumber)
        {
        case 1:
        {
            html.replace("МЕТКА_КОД_ОКУД", "");
            html.replace("МЕТКА_КОД_ОКПО", "");
            html.replace("МЕТКА_ДИАГНОЗ", "");
            html.replace("МЕТКА_ЖАЛОБЫ", "");
            html.replace("МЕТКА_ФИО", "");
            html.replace("МЕТКА_ПОЛ", "");
            html.replace("МЕТКА_ВОЗРАСТ", "");
            html.replace("МЕТКА_АДРЕС", "");
            html.replace("МЕТКА_ПРОФЕССИЯ", "");
            break;
        }
        case 2:
        {
            html.replace("МЕТКА_ИССЛЕДОВАНИЕ1", "");
            html.replace("МЕТКА_ИССЛЕДОВАНИЕ2", "");
            html.replace("МЕТКА_ИССЛЕДОВАНИЕ3", "");
            html.replace("МЕТКА_ИССЛЕДОВАНИЕ4", "");
            html.replace("МЕТКА_ИССЛЕДОВАНИЕ5", "");
            html.replace("МЕТКА_ИССЛЕДОВАНИЕ6", "");
            html.replace("МЕТКА_ИССЛЕДОВАНИЕ7", "");

            html.replace("МЕТКА_СОСТОЯНИЕ", "");

            html.replace("МЕТКА_ПРИКУС", "");

            html.replace("МЕТКА_РЕНТГЕН1", "");
            html.replace("МЕТКА_РЕНТГЕН2", "");
            html.replace("МЕТКА_РЕНТГЕН3", "");
            html.replace("МЕТКА_РЕНТГЕН4", "");
            break;
        }
        case 3:
        {
            html.replace("МЕТКА_ЛЕЧЕНИЕ1", ".");
            html.replace("МЕТКА_ЛЕЧЕНИЕ2", ".");
            html.replace("МЕТКА_ЛЕЧЕНИЕ3", ".");
            html.replace("МЕТКА_ЛЕЧЕНИЕ4", ".");
            html.replace("МЕТКА_ЛЕЧЕНИЕ5", ".");

            html.replace("МЕТКА_ЭПИКРИЗ1", ".");
            html.replace("МЕТКА_ЭПИКРИЗ2", ".");
            html.replace("МЕТКА_ЭПИКРИЗ3", ".");
            html.replace("МЕТКА_ЭПИКРИЗ4", ".");
            html.replace("МЕТКА_ЭПИКРИЗ5", ".");

            html.replace("МЕТКА_НАСТАВЛЕНИЯ1", ".");
            html.replace("МЕТКА_НАСТАВЛЕНИЯ2", ".");
            html.replace("МЕТКА_НАСТАВЛЕНИЯ3", ".");
            html.replace("МЕТКА_НАСТАВЛЕНИЯ4", ".");
            html.replace("МЕТКА_НАСТАВЛЕНИЯ5", ".");

            html.replace("МЕТКА_ВРАЧ", currentDoctorInitials);
            html.replace("МЕТКА_ЗАВЕДУЩ", ".");
            break;
        }
        case 4:
        {
            html.replace("МЕТКА_ДАТА", ".");

            html.replace("МЕТКА_ЖАЛОБЫ1", ".");
            html.replace("МЕТКА_ЖАЛОБЫ2", ".");
            html.replace("МЕТКА_ЖАЛОБЫ3", ".");
            html.replace("МЕТКА_ЖАЛОБЫ4", ".");
            html.replace("МЕТКА_ЖАЛОБЫ5", ".");

            html.replace("МЕТКА_АНАМНЕЗ1", ".");
            html.replace("МЕТКА_АНАМНЕЗ2", ".");

            html.replace("МЕТКА_ОСМОТР1", ".");
            html.replace("МЕТКА_ОСМОТР2", ".");
            html.replace("МЕТКА_ОСМОТР3", ".");
            html.replace("МЕТКА_ОСМОТР4", ".");
            html.replace("МЕТКА_ОСМОТР5", ".");

            html.replace("МЕТКА_ОБЪЕКТИВНО1", ".");
            html.replace("МЕТКА_ОБЪЕКТИВНО2", ".");
            html.replace("МЕТКА_ОБЪЕКТИВНО3", ".");
            html.replace("МЕТКА_ОБЪЕКТИВНО4", ".");
            html.replace("МЕТКА_ОБЪЕКТИВНО5", ".");
            html.replace("МЕТКА_ОБЪЕКТИВНО6", ".");
            html.replace("МЕТКА_ОБЪЕКТИВНО7", ".");

            html.replace("МЕТКА_РЕНТГЕН1", ".");
            html.replace("МЕТКА_РЕНТГЕН2", ".");
            html.replace("МЕТКА_РЕНТГЕН3", ".");

            html.replace("МЕТКА_ДИАГНОЗ", ".");
            break;
        }
        }
        webView->setHtml(html);
        loop.exec();

        webView->page()->printToPdf(path);
        loop.exec();
    }

}

// FIXME: Вынести в отдельный поток
void PatientDataBase::generateDiary(Record_t record, QString path)
{
    std::vector<QString> paths;

    QFile file("://cards_src/page4.html");
    file.open(QIODevice::ReadOnly);

    QTextStream input(&file);
    input.setCodec( "utf-8" );
    QString html = input.readAll();

    file.close();

    QString finalExtenstionName;
    QString formattedDate = record.date;

    // Меняем в дате точки на нижнее подчёркивание, чтобы не было конфликтов при сохранении
    formattedDate.replace(".", "_");
    finalExtenstionName.append("_" + formattedDate + ".pdf");

    // Заменяем у пути имя на <дата_записи>.pdf
    path.replace(".pdf", finalExtenstionName);

    html.replace("МЕТКА_ДАТА", record.date);

    fillComplaints(record, &html);
    fillAnamnesis(record, &html);
    fillExternalInspection(record, &html);

    html.replace("МЕТКА_РЕНТГЕН1", ".");
    html.replace("МЕТКА_РЕНТГЕН2", ".");
    html.replace("МЕТКА_РЕНТГЕН3", ".");

    if (record.currentDiagnosis.size() == 0)
        html.replace("МЕТКА_ДИАГНОЗ", ".");
    else
        html.replace("МЕТКА_ДИАГНОЗ", record.currentDiagnosis);

    webView->setHtml(html);
    loop.exec();

    webView->page()->printToPdf(path);
    loop.exec();

    paths.push_back(path);

    // Страница лечения и результатов лечения
    QFile file2("://cards_src/page3.html");
    file2.open(QIODevice::ReadOnly);

    QTextStream input2(&file2);
    input2.setCodec( "utf-8" );
    html = input2.readAll();

    file2.close();

    path.replace(".pdf", "_treatment.pdf");

    fillTreatment(record, &html);
    fillTreatmentResult(record, &html);

    html.replace("МЕТКА_НАСТАВЛЕНИЯ1", ".");
    html.replace("МЕТКА_НАСТАВЛЕНИЯ2", ".");
    html.replace("МЕТКА_НАСТАВЛЕНИЯ3", ".");
    html.replace("МЕТКА_НАСТАВЛЕНИЯ4", ".");
    html.replace("МЕТКА_НАСТАВЛЕНИЯ5", ".");

    html.replace("МЕТКА_ВРАЧ", currentDoctorInitials);
    html.replace("МЕТКА_ЗАВЕДУЩ", ".");

    webView->setHtml(html);
    loop.exec();

    webView->page()->printToPdf(path);
    loop.exec();

    paths.push_back(path);

    path.replace("_treatment.pdf", "_diary.pdf");

    PDFWriter writer;

    writer.StartPDF(path.toStdString(), ePDFVersion13);

    for (const auto &path : paths)
    {
        writer.AppendPDFPagesFromPDF(path.toStdString(), PDFPageRange());
        QFile::remove(path.toStdString().c_str());
    }

    writer.EndPDF();
}

// FIXME: Вынести в отдельный поток
/**
 * @brief Заполнение данных дневника лечения
 * @param birthDate
 * @param paths
 */
void PatientDataBase::generateDiary(QString birthDate, std::vector<std::string> *paths)
{
    QList<Record_t> records;

    // Вытаскиваем все записи для поочерёдного заполнения
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            records = p.cardRecords;
            break;
        }
    }
    // Изначальный путь до 4-й страницы с дневников
    QString path = paths->back().c_str();

    for (const auto &recIt : records)
    {
        QFile file("://cards_src/page4.html");
        file.open(QIODevice::ReadOnly);

        QTextStream input(&file);
        input.setCodec( "utf-8" );
        QString html = input.readAll();

        file.close();

        // Мы каждый раз берём изначальный путь без модификаций, чтобы в него без последствий вписать новое имя
        QString oldPath = path;

        QString finalExtenstionName;
        QString formattedDate = recIt.date;

        // Меняем в дате точки на нижнее подчёркивание, чтобы не было конфликтов при сохранении
        formattedDate.replace(".", "_");
        finalExtenstionName.append("_" + formattedDate + ".pdf");

        // Заменяем у пути имя на <дата_записи>.pdf
        oldPath.replace(".pdf", finalExtenstionName);

        html.replace("МЕТКА_ДАТА", recIt.date);

        fillComplaints(recIt, &html);
        fillAnamnesis(recIt, &html);
        fillExternalInspection(recIt, &html);

        html.replace("МЕТКА_РЕНТГЕН1", ".");
        html.replace("МЕТКА_РЕНТГЕН2", ".");
        html.replace("МЕТКА_РЕНТГЕН3", ".");

        if (recIt.currentDiagnosis.size() == 0)
            html.replace("МЕТКА_ДИАГНОЗ", ".");
        else
            html.replace("МЕТКА_ДИАГНОЗ", recIt.currentDiagnosis);

        webView->setHtml(html);
        loop.exec();

        // Записываем изменённый путь в массив
        paths->push_back(oldPath.toStdString());

        webView->page()->printToPdf(oldPath);
        loop.exec();

        // Страница лечения и результатов лечения
        QFile file2("://cards_src/page3.html");
        file2.open(QIODevice::ReadOnly);

        QTextStream input2(&file2);
        input2.setCodec( "utf-8" );
        html = input2.readAll();

        file2.close();

        oldPath.replace(".pdf", "_treatment.pdf");

        fillTreatment(recIt, &html);
        fillTreatmentResult(recIt, &html);

        html.replace("МЕТКА_НАСТАВЛЕНИЯ1", ".");
        html.replace("МЕТКА_НАСТАВЛЕНИЯ2", ".");
        html.replace("МЕТКА_НАСТАВЛЕНИЯ3", ".");
        html.replace("МЕТКА_НАСТАВЛЕНИЯ4", ".");
        html.replace("МЕТКА_НАСТАВЛЕНИЯ5", ".");

        html.replace("МЕТКА_ВРАЧ", currentDoctorInitials);
        html.replace("МЕТКА_ЗАВЕДУЩ", ".");

        webView->setHtml(html);
        loop.exec();

        // Записываем изменённый путь в массив
        paths->push_back(oldPath.toStdString());

        webView->page()->printToPdf(oldPath);
        loop.exec();

    }
}

// FIXME: Вынести в отдельный поток
void PatientDataBase::generateFullCard(QString birthDate, QString path)
{
    QString patientName;
    QString sex;
    QString age;
    QString address;
    QString occupation;

    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            // Для подстановки ФИО в карту
            patientName = p.fullName;
            sex = p.sex == false ? "М" : "Ж";
            age = QString::number(p.age);
            address = p.address;
            occupation = p.occupation;
            break;
        }
    }

    QFile file("://cards_src/page1.html");
    file.open(QIODevice::ReadOnly);

    QTextStream input(&file);
    input.setCodec( "utf-8" );
    QString html = input.readAll();

    file.close();

    QFile file1("://cards_src/page2.html");
    file1.open(QIODevice::ReadOnly);

    QTextStream input1(&file1);
    input1.setCodec( "utf-8" );
    QString html1 = input1.readAll();

    file1.close();

    QFile file3("://cards_src/page4.html");
    file3.open(QIODevice::ReadOnly);

    QTextStream input3(&file3);
    input3.setCodec( "utf-8" );
    QString html3 = input3.readAll();

    file3.close();

    QFile file4("://cards_src/page5.html");
    file4.open(QIODevice::ReadOnly);

    QTextStream input4(&file4);
    input4.setCodec( "utf-8" );
    QString html4 = input4.readAll();

    file4.close();

    // 1 страница
    html.replace("МЕТКА_КОД_ОКУД", "");
    html.replace("МЕТКА_КОД_ОКПО", "");
    html.replace("МЕТКА_ДИАГНОЗ", "");
    html.replace("МЕТКА_ЖАЛОБЫ", "");
    html.replace("МЕТКА_ФИО", patientName);
    html.replace("МЕТКА_ПОЛ", sex);
    html.replace("МЕТКА_ВОЗРАСТ", age);
    html.replace("МЕТКА_АДРЕС", address);
    html.replace("МЕТКА_ПРОФЕССИЯ", occupation);

    webView->setHtml(html);
    loop.exec();

    paths.push_back(path.toStdString());
    webView->page()->printToPdf(path);
    loop.exec();

    path.replace(".pdf", "_1.pdf");
    paths.push_back(path.toStdString());

    // 2 страница
    html1.replace("МЕТКА_ИССЛЕДОВАНИЕ1", "");
    html1.replace("МЕТКА_ИССЛЕДОВАНИЕ2", "");
    html1.replace("МЕТКА_ИССЛЕДОВАНИЕ3", "");
    html1.replace("МЕТКА_ИССЛЕДОВАНИЕ4", "");
    html1.replace("МЕТКА_ИССЛЕДОВАНИЕ5", "");
    html1.replace("МЕТКА_ИССЛЕДОВАНИЕ6", "");
    html1.replace("МЕТКА_ИССЛЕДОВАНИЕ7", "");

    html1.replace("МЕТКА_СОСТОЯНИЕ", "");

    html1.replace("МЕТКА_ПРИКУС", "");

    html1.replace("МЕТКА_РЕНТГЕН1", "");
    html1.replace("МЕТКА_РЕНТГЕН2", "");
    html1.replace("МЕТКА_РЕНТГЕН3", "");
    html1.replace("МЕТКА_РЕНТГЕН4", "");

    webView->setHtml(html1);
    loop.exec();

    webView->page()->printToPdf(path);
    loop.exec();

    path.replace("_1.pdf", "_2.pdf");
    paths.push_back(path.toStdString());

    path.replace("_2.pdf", "_3.pdf");
    paths.push_back(path.toStdString());

    // 4 страница
    webView->setHtml(html3);
    loop.exec();

    // Генерация дневников
    // TODO: Печатается 3-4 страницы
    generateDiary(birthDate, &paths);

    path.replace("_3.pdf", "_4.pdf");
    paths.push_back(path.toStdString());

    webView->setHtml(html4);
    loop.exec();

    webView->page()->printToPdf(path);
    loop.exec();

    path.remove("_4.pdf");

    std::string finalPdfPath = path.toStdString();
    finalPdfPath += "_generated.pdf";

    PDFWriter writer;

    writer.StartPDF(finalPdfPath, ePDFVersion13);

    for (const auto &path : paths)
    {
        writer.AppendPDFPagesFromPDF(path, PDFPageRange());
        QFile::remove(path.c_str());
    }

    writer.EndPDF();

    paths.clear();
}

/**
 * @brief Сохраняет профиль пациента в patients.json по указанному параметру
 * @param patientProfile
 */
void PatientDataBase::saveProfileToJson(Patient patientProfile)
{
    QJsonDocument jsonDocument = loadJson();

    QJsonArray jsonArray = jsonDocument.array();
    QJsonArray patientProfileRecords;

    QJsonObject PatientProfileObj;

    patientProfileRecords = convertRecordsToJsonArray(patientProfile.cardRecords);

    PatientProfileObj.insert("fullname", patientProfile.fullName);
    PatientProfileObj.insert("age", patientProfile.age);
    PatientProfileObj.insert("sex", patientProfile.sex);
    PatientProfileObj.insert("birthdate", patientProfile.birthDate);
    PatientProfileObj.insert("address", patientProfile.address);
    PatientProfileObj.insert("phoneNumber", patientProfile.phoneNumber);
    PatientProfileObj.insert("occupation", patientProfile.occupation);

    PatientProfileObj.insert("records", patientProfileRecords);

    jsonArray.append(PatientProfileObj);

    jsonDocument.setArray(jsonArray);

    QFile jsonFile(JSON_PATIENT_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();

    qDebug() << "\t[PatienDataBase::saveProfileToJson()] - Profile saved\n";
}

bool PatientDataBase::isProfileExists(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return false;

    foreach (Patient currentDoctor, *patientsList)
    {
        if (currentDoctor.birthDate == birthDate)
            return true;
        else
            continue;
    }
    return false;
}

/**
 * @brief Загружает содержимое файла patients.json
 * @return
 */
QJsonDocument PatientDataBase::loadJson()
{
    QFileInfo fInfo(JSON_PATIENT_FILE_PATH);
    QFile f(JSON_PATIENT_FILE_PATH);

    if (fInfo.exists() == false)
    {
        f.open(QFile::WriteOnly);
        QJsonDocument jd;
        f.write(jd.toJson());
        f.close();
        return jd;
    }

    f.open(QFile::ReadOnly);
    QJsonDocument jd = QJsonDocument::fromJson(f.readAll());
    f.close();
    return jd;
}

/**
 * @brief Конвертирует QList в массив формата JSON
 * @param list
 * @return
 */
QJsonArray PatientDataBase::convertListToJsonArray(const QList<QString> &list)
{
    QJsonArray array;

    if (list.isEmpty() == true)
        return array;

    for (const auto &data : list)
        array.append(data);

    return array;
}

/**
 * @brief Конвертирует лист записей в массив формата JSON
 * @param records
 * @return
 */
QJsonArray PatientDataBase::convertRecordsToJsonArray(const QList<Record_t> &records)
{
    QJsonArray array;

    if (records.isEmpty() == true)
        return array;

    for (const auto &data : records)
    {
        QJsonObject recordObject;

        recordObject.insert("data", data.date);
        recordObject.insert("diagnosis", data.currentDiagnosis);

        recordObject.insert("anamnesis", data.anamnesis);
        recordObject.insert("treatment", data.treatment);
        recordObject.insert("complaints", data.complaints);
        recordObject.insert("diseases", data.diseases);
        recordObject.insert("treatmentResult", data.treatmentResult);

        array.append(recordObject);
    }
    return array;
}

/**
 * @brief Конвертирует записи формата JSON в QList
 * @param recordsArray
 * @return
 */
QList<Record_t> PatientDataBase::convertJsonRecordsToList(const QJsonArray recordsArray)
{
    QList<Record_t> tmpArray;
    Record_t tmpRecord;

    for (const auto &record : recordsArray)
    {
        tmpRecord.date = record["data"].toString();
        tmpRecord.anamnesis = record["anamnesis"].toString();
        tmpRecord.diseases = record["diseases"].toString();
        tmpRecord.complaints = record["complaints"].toString();
        tmpRecord.currentDiagnosis = record["diagnosis"].toString();
        tmpRecord.treatment = record["treatment"].toString();
        tmpRecord.treatmentResult = record["treatmentResult"].toString();

        tmpArray.append(tmpRecord);
    }
    return tmpArray;
}
