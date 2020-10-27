#include "xmlcontroller.h"

XMLController::XMLController(Editor *e, QString filePath):LangController(e,filePath,"xml"){
    QString content = editor->document()->toPlainText();
    DataTree tree(content);
    Block *root = tree.getRoot();
    _readTree(root,0, tagList, l_queue);
    QStringListModel *strModel = qobject_cast<QStringListModel*>(completer->model());
    for(QString tag : tagList) strModel->setStringList(strModel->stringList() << tag);
}

void XMLController::onTextChanged(){
}

XMLController::~XMLController(){
}

int XMLController::getSynsetNumber(){return synsetNumber;}

void XMLController::minify(){
    QString content = editor->document()->toPlainText();
    content.replace("\t","");
    content.replace("\n","");
    editor->document()->setPlainText(content);
}

void XMLController::_readTree(Block *root, int level, QList<QString> &tagList, QList<QPair<Info, int>> &queue){
    if(root->getName().compare("root")){
        Info i;
        i.attr = nullptr;
        i.tagName = root->getName();
        i.type = root->getTagType();
        if(root->getAttributes() != nullptr) i.attr = root->getAttributes();
        if(!root->getName().compare("synset")) synsetNumber++;
        queue.append(QPair<Info, int>(i,level));
    }
    if(root->getValue() != nullptr){
        QString name = root->getName();
        if(!name.compare("root")){
            for(Block *b : *(root->getValue())) _readTree(b, level, tagList, queue);
        }else{
            if(!tagList.contains(name)) tagList.append(name);
            for(Block *b : *(root->getValue())) _readTree(b, level+1, tagList, queue);
        }
    }
}

void XMLController::beautify(){
    QString content = editor->document()->toPlainText();
    DataTree tree(content);
    Block *root = tree.getRoot();
    l_queue.clear();
    _readTree(root,0, tagList, l_queue);
    editor->document()->setPlainText(_buildXML(l_queue));

}

void traverseTree(Block *root, Trie<QList<Block*>*> *trie){
    if(!root->getName().compare("synset")){
        QString word;
        for(Block *b : *(root->getValue())){
            if(b->getName() == "word"){
                word = (*(b->getValue()))[0]->getName();
                if(trie->contains(word)){
                    trie->getValue(word)->append(root);
                }else{
                    QList<Block*> *l = new QList<Block*>;
                    l->append(root);
                    trie->add(word, l);
                }
            }
        }
    }
    if(root->getValue() != nullptr)
        for(Block *b : *(root->getValue())) traverseTree(b, trie);
}

Trie<QList<Block*>*>* XMLController::getBlockTrie(){
    Trie<QList<Block*>*>* trie = new Trie<QList<Block*>*>();
    QString content = editor->document()->toPlainText();
    DataTree *tree = new DataTree(content);
    Block *root = tree->getRoot();
    traverseTree(root, trie);
    return trie;
}

void XMLController::showSynsetInfo(){
    QString fileName = filePath.mid(filePath.lastIndexOf("/")+1);
    Trie<QList<Block*>*>*t = this->getBlockTrie();
    SynsetInfo *s = new SynsetInfo(t, fileName);
    s->setFixedSize(400,600);
    s->move(QApplication::desktop()->screen()->rect().center() - s->rect().center());
    s->show();
}

void XMLController::convert2JSON(){
    QString jsonName = filePath.mid(0, filePath.lastIndexOf("."))+".json";
    QString content = editor->document()->toPlainText();
    DataTree tree(content);
    FilesConverter f(&tree,jsonName);
    f.generateJSONFile();
}

QString XMLController::_buildXML(QList<QPair<Info, int>> &queue){
    QString xml = "";
    QVector<QPair<Info, int> > stack;
    int lastLevel = 0;
    int size = queue.size();
    for(int c = 0; c < size; c++){
        QPair<Info, int> token = queue[0];
        queue.pop_front();
        qDebug() << "Remaining" << queue.size();
        // Printing closing tabs if the token level is less than the last level
        if(lastLevel > token.second){
            int l = lastLevel;
            while(true){
                if(stack[stack.size()-1].second < token.second) break; // token level is greater than curren tag in stack
                l--;
                if(l != lastLevel-1)
                    for(int a = 0; a < l; a++) xml+="\t";
                xml += "</"+stack[stack.size()-1].first.tagName+">\n";
                stack.pop_back();
                if(stack.size() == 0)break;
            }
        }

        lastLevel = token.second;

        if(token.first.type == STRING){
            xml += token.first.tagName;
        }else if(token.first.type == NORMAL){
            for(int a = 0; a < token.second; a++) xml+="\t"; // printing spaces
            xml += "<"+token.first.tagName;
            if(token.first.attr == nullptr) xml += ">";
            else{
                xml += " ";
                for(QString k : token.first.attr->keys()){
                    xml += k + "=\"" + token.first.attr->value(k) + "\" ";
                }
                xml.remove(xml.size()-1,1);
                xml += ">";
            }
            stack.append(token);
        }else if(token.first.type == SELF_ENDED){
            for(int a = 0; a < token.second; a++) xml+="\t"; // printing spaces
            xml += "<"+token.first.tagName;
            if(token.first.attr == nullptr) xml += "/>";
            else{
                xml += " ";
                for(QString k : token.first.attr->keys()){
                    xml += k + "=\"" + token.first.attr->value(k) + "\" ";
                }
                xml.remove(xml.size()-1,1);
                xml += "/>";
            }
        }else if(token.first.type == INFO){
            for(int a = 0; a < token.second; a++) xml+="\t"; // printing spaces
            xml += "<?"+token.first.tagName;
            if(token.first.attr == nullptr) xml += "?>";
            else{
                xml += " ";
                for(QString k : token.first.attr->keys()){
                    xml += k + "=\"" + token.first.attr->value(k) + "\" ";
                }
                xml.remove(xml.size()-1,1);
                xml += "?>";
            }
        }

        if(token.first.type != STRING && queue.size() != 0 && queue[0].first.type != STRING) xml += "\n";
    }
    if(stack.size()){
        xml += "</"+stack[stack.size()-1].first.tagName+">\n";
        stack.pop_back();
        lastLevel -= 2;
        while(true){
            if(stack.size() == 0)break;
            for(int a = 0; a < lastLevel; a++) xml += "\t";
            lastLevel --;
            xml += "</"+stack[stack.size()-1].first.tagName+">\n";
            stack.pop_back();
        }
    }
    return xml;
}
