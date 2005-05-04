#ifndef __MRENAME_H
#define __MRENAME_H

class MRename : public Message {
  inodeno_t srcdirino;
  string srcname;
  inodeno_t destdirino;
  string destname;

  crope inode_state;

 public:
  inodeno_t get_srcdirino() { return srcdirino; }
  string& get_srcname() { return srcname; }
  inodeno_t get_destdirino() { return destdirino; }
  string& get_destname() { return destname; }

  MRename() {}
  MRename(inodeno_t srcdirino,
				const string& srcname,
				inodeno_t destdirino,
				const string& destname,
				crope& inode_state) :
	Message(MSG_MDS_RENAME) {
	this->srcdirino = srcdirino;
	this->srcname = srcname;
	this->destdirino = destdirino;
	this->destname = destname;
	this->inode_state = inode_state;
  }
  virtual char *get_type_name() { return "Rnot";}

  crope& get_inode_state() { return inode_state; }
  
  virtual void decode_payload(crope& s) {
	int off = 0;
	s.copy(off, sizeof(srcdirino), (char*)&srcdirino);
	off += sizeof(srcdirino);
	s.copy(off, sizeof(destdirino), (char*)&destdirino);
	off += sizeof(destdirino);
	srcname = s.c_str() + off;
	off += srcname.length() + 1;
	destname = s.c_str() + off;
	off += destname.length() + 1;
	inode_state = s.substr(off, s.length()-off);
  }
  virtual void encode_payload(crope& s) {
	s.append((char*)&srcdirino,sizeof(srcdirino));
	s.append((char*)&destdirino,sizeof(destdirino));
	s.append((char*)srcname.c_str());
	s.append((char)0);
	s.append((char*)destname.c_str());
	s.append((char)0);
	s.append(inode_state);
  }
};

#endif
