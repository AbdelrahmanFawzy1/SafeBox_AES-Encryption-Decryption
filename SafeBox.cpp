#include <SafeBox.h>
#include<FileSpooler.h>
#include <random>
#include<string>
#include<sstream>

SafeBox::SafeBox ()
{ // Invocation to avl by just calling it 
  avl= new AVLTree<AVL_Node_index_t> ();

}
SafeBox::~SafeBox()
{
}
// This function is important for many reasons
// Like I need to generate iv at first, decrypte the Index_file, read it, and so on..
 void SafeBox::tree_process(char * Index_file, char * key_file, char * iv_file)
        {
           // This function basically will try to generate the iv and decrypt the file
            CryptoPP::byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
            memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
            memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
long size ;
char* buffer;
            std::ifstream f_tree("treeindex.txt",ios::in);
                if ( f_tree.is_open())
                    { // Here it is the nearly same logic as theMulti-Head Queue.
                        f_tree.seekg(0,f_tree.end); // To read from the ending of the file
                         size = f_tree.tellg();// Get the size
                        f_tree.seekg(0,f_tree.beg); 
                         buffer = (char *) calloc (size,sizeof(char));
                        f_tree.read (buffer,size);
                        f_tree.close();}
            std::ifstream key1(key_file,ios::in);
                if ( key1.is_open())
                {
                    key1.read (reinterpret_cast<char*>(key),sizeof(key)); 
                    key1.close();
                 }
              std::ifstream fiv("output/iv.txt",ios::in);

            if ( fiv.peek() == std::ifstream::traits_type::eof()){ // If it is empty, you can get a new line.
            std::ofstream f; 
            f.open("output/iv.txt", ios::out | ios::trunc); 
            //fiv.read(reinterpret_cast< char*>(iv),sizeof(iv));
           // if (strcmp(reinterpret_cast< char*>(iv), "")==0) {     
            memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
            AutoSeededRandomPool prng; // To generate the iv
            prng.GenerateBlock(iv,sizeof(iv));
            f.write (reinterpret_cast<const char*>(iv),sizeof(iv));
            f.close();// 
           fiv.close();
            }
      //    while(size%CryptoPP::AES::BLOCKSIZE!=0){ //This is while loop to handle the padding by ourselves. 
        //             size++;    // ++ till get the number as the encrypted to solve the padding
          //      } 
    //if (size == 0)return; 
else { // The same as 
        /*    std::string decryptedtext;
            CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
            CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv);
            CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ),CryptoPP::StreamTransformationFilter::ZEROS_PADDING );
            stfDecryptor.Put( reinterpret_cast<const unsigned char*>( buffer ), decryptedtext.size());
            stfDecryptor.MessageEnd();
            memmove(buffer,decryptedtext.c_str(),decryptedtext.size()); 
cout << " BUFFER " << buffer << endl; 
cout << key << "  "<< " IV"<< iv << endl; 
*/	string tok = "";
        long size;
        long size_in_blocks;
        long size_in_bytes;
        long shreds_number;
        string hidden_name;	
 	string name;
string line = "";

	while(getline(f_tree,line)) { 
        AVL_Node_index_t var;
        		std::stringstream iss(line); // Instantiate stringstream with the current line just read

		std::getline(iss, var.filename, ','); // parse name
		std::getline(iss, tok, ','); // parse size
        var.blocksize = strtof(tok.c_str(),NULL);		
        std::getline(iss, tok, ','); // parse size_in_blocks
       var.size_in_blocks = strtof(tok.c_str(),NULL);				
        std::getline(iss, tok, ','); // parse size_in_bytes
        var.size_in_bytes = strtof(tok.c_str(),NULL);				
        std::getline(iss, tok, ','); // parse shreds_number
        var.shreds= strtof(tok.c_str(),NULL);		
		std::getline(iss, tok, ','); // parse hidden_nam
            
            avl-> insert(var);
            }
           
        
         }                      
         }   void SafeBox::Index_process(char * Index_file, char * key_file_name, char * iv_file){
            
            CryptoPP::byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
            memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
            memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
// This is to decrypt the file 
                     
                     std::ifstream kf;
                     kf.open(key_file_name,ios::in);
                 if ( kf.is_open())
                    {
                    kf.read (reinterpret_cast<char*>(key),sizeof(key));
                    kf.close();
                    }

                std::ifstream fiv;
                    fiv.open("output/iv.txt",ios::in);
                 if ( fiv.is_open())
                    {
                      fiv.read(reinterpret_cast< char*>(iv),sizeof(iv));
                      fiv.close();
                }
               std::fstream index;
                index.open("treeindex.txt",ios::app|ios::out);  // To open the treeindex
                avl->traverseASC(index);
                cout << " WOW "<< endl; 
                index.close();
              /*  std::fstream indx_read("treeindex.txt",ios::in|ios::out);
                     indx_read.seekg(0,index.end);
                     long size = indx_read.tellg();
                        indx_read.seekg(0,indx_read.beg);
                        char* buffer = (char *) calloc (size,sizeof(char));
                        indx_read.read (buffer,size);
            */}
            /*     std::string ciphertext; //Typical as the block No thing difference
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( buffer),size );// BE careful the vector data is point of integar, so it needs casting
    stfEncryptor.MessageEnd(); // I need to get all of them
    memcpy (buffer,ciphertext.c_str(),ciphertext.size());  
    indx_read.write(reinterpret_cast<const char*>(buffer),ciphertext.size());    
    indx_read.close();
                        
                }*/
SafeBoxImport::SafeBoxImport(){

}
void SafeBoxImport::process (char * input_file,
                            char * output_file,
                            char * working_dir,
                            char * key_file,
                            uint16_t block_size,
                            uint16_t shreds,
                             bool flag){
                                
                    printf ("Import file\n");
                    char outf [1024];
                    char outiv [1024];
                    char outq [1024];
                    memset (outf,0,1024);
                    memset (outq,0,1024);

                    sprintf (outf,"%s/%s",working_dir,output_file);
                    sprintf (outiv,"%s/%s.iv",working_dir,output_file);
                    sprintf (outq,"%s/%s.queue",working_dir,output_file); 
                    
                    
        tree_process("treeindex.txt",key_file, "output/iv.txt");
            cout << " A"<< endl; 

                    mt19937 generator{random_device{}()};
                  uniform_int_distribution<int> distribution{'a', 'z'};
                     auto generate_len = 5; 
                 string rand_str(generate_len, '\0');
              for(auto& dis: rand_str)
               dis = distribution(generator); 
                               //     sprintf ((char*)rand_str.c_str(),"%s/%s",working_dir,output_file); 

 /*  char rand_str[8];
    for (int i = 0; i < 8; ++i)
        rand_str[i] = ((double)rand() / ((double)RAND_MAX + 1.0)) * ('z' - 'a' + 1) + 'a';
    rand_str[8] = '\0';*/
    // Import will get the strct of AV_NODE and insert it in the tree
            FileSpooler fileSpooler (input_file,block_size,false);
            AVL_Node_index_t strct;
            strct.filename= input_file;
            strct.blocksize=block_size; 
            strct.size_in_blocks= fileSpooler.getBlockCount();
            strct.size_in_bytes = fileSpooler.fsize;
            strct.shreds = shreds; 
            strct.hidden_name=rand_str;
            strct.flag=false;
            avl-> insert(strct);
            MultithreadedShredManager shredManager((char*)rand_str.c_str(), block_size, shreds,true);       
            shredManager.encrypt(&fileSpooler,key_file,"output/iv.txt",outq);  // To get one iv.
            Index_process("treeindex.txt",key_file, "output/iv.txt");

}
SafeBox * SafeBoxImport::clone (){
    return new SafeBoxImport();
}
SafeBoxImport::~SafeBoxImport(){

}

SafeBoxExport::SafeBoxExport (){

}
void SafeBoxExport::process (char * input_file,
                            char * output_file,
                            char * working_dir,
                            char * key_file,
                            uint16_t block_size,
                            uint16_t shreds,
                            bool flag){
        tree_process("treeindex.txt",key_file, "iv.txt");
        // Ot os to make a string and inpurt file
                AVLTree<AVL_Node_index_t> *bst1;
                AVL_Node_index_t strct;
                strct.filename=input_file; 
                       AVLNode<AVL_Node_index_t>*x= bst1->find(strct);
                       string input= x->getItem().hidden_name;
                                printf ("Export file\n");
                                char inf [1024];
                                char inq [1024];
                                memset (inf,0,1024);
                                memset (inq,0,1024);
                                sprintf (inf,"%s/%s",working_dir,(char*)input.c_str());
                                sprintf (inq,"%s/%s.queue",working_dir,(char*)input.c_str());
                                                            
                MultithreadedShredManager shredManager(inf, block_size, shreds,false);   // Here is the part of edcryption.                                                                    
                FileSpooler fileSpooler (output_file,block_size,true);
                shredManager.decrypt(&fileSpooler,key_file,"output/iv.txt",inq);
                            Index_process("treeindex.txt",key_file, "output/iv.txt");

                // The same as import but just decrypting the blocks. 
                // The more details will include in the other functions, but generally, the safe box is just calling the constructor 
              //  and its preporities  : decrypted function.
}
SafeBox * SafeBoxExport::clone (){
    return new SafeBoxExport();
}
SafeBoxExport::~SafeBoxExport(){
}
/*************************************************** SafeBox List Class***************************************************/
SafeBoxList::SafeBoxList(){
}
void SafeBoxList::process(char * input_file,
                            char * output_file,
                            char * working_dir,
                            char * key_file,
                            uint16_t block_size,
                            uint16_t shreds,
                              bool flag){
avl->process([](AVLNode<AVL_Node_index_t>* n)->void{ // Lambda function to get what I need ( PRINTING)
cout << n->getItem().filename << ", " << n->getItem().blocksize<< ", " << n->getItem().size_in_blocks << n->getItem().shreds << n->getItem().hidden_name << n->getItem().flag;
},flag);
}
SafeBox * SafeBoxList::clone (){
    return new SafeBoxList();
}
SafeBoxList::~SafeBoxList(){
}


/*************************************************** SafeBox Delete Class***************************************************/

SafeBoxDelete::SafeBoxDelete() 
{
}
void SafeBoxDelete::process(char * input_file,
                            char * output_file,
                            char * working_dir,
                            char * key_file,
                            uint16_t block_size,
                            uint16_t shreds,
                              bool flag){
AVL_Node_index_t x;
x.filename=input_file; 
avl->find(x)->getItem().flag= false;  // Here is to delete .
}
SafeBox * SafeBoxDelete::clone(){
    return new SafeBoxDelete();
}
SafeBoxDelete::~SafeBoxDelete() 
{}