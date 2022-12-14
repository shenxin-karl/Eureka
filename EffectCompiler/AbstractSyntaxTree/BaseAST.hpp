#pragma once

extern int getCurrentLineNo();
extern int getCurrentColumnNo();

namespace EC {

class BaseAST {
public:
	BaseAST() = default;
	virtual ~BaseAST() = default;
public:
	int lineNo = getCurrentLineNo();
	int columnNo = getCurrentColumnNo();
};

}
