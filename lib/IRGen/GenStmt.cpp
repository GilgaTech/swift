//===--- GenStmt.cpp - IR Generation for Statements -----------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
//  This file implements IR generation for Swift statements.
//
//===----------------------------------------------------------------------===//

#include "swift/AST/Stmt.h"
#include "llvm/ADT/PointerUnion.h"
#include "llvm/Support/ErrorHandling.h"
#include "Cleanup.h"
#include "IRGenFunction.h"

using namespace swift;
using namespace irgen;

void IRGenFunction::emitStmt(Stmt *S) {
  switch (S->Kind) {
  case StmtKind::Semi:
    // Nothing to do.
    return;

  case StmtKind::Assign:
    return emitAssignStmt(cast<AssignStmt>(S));

  case StmtKind::Brace:
    return emitBraceStmt(cast<BraceStmt>(S));

  case StmtKind::Return:
    return emitReturnStmt(cast<ReturnStmt>(S));

  case StmtKind::If:
    return emitIfStmt(cast<IfStmt>(S));

  case StmtKind::While:
    return emitWhileStmt(cast<WhileStmt>(S));
  }
  llvm_unreachable("bad statement kind!");
}

void IRGenFunction::emitBraceStmt(BraceStmt *BS) {
  // Enter a new scope.
  Scope BraceScope(*this);

  for (unsigned I = 0, E = BS->NumElements; I != E; ++I) {
    BraceStmt::ExprStmtOrDecl Elt = BS->Elements[I];
    if (Expr *E = Elt.dyn_cast<Expr*>()) {
      emitIgnored(E);
    } else if (Stmt *S = Elt.dyn_cast<Stmt*>()) {
      emitStmt(S);
    } else {
      emitLocal(Elt.get<Decl*>());
    }
  }
}

void IRGenFunction::emitAssignStmt(AssignStmt *S) {
  unimplemented(S->getLocStart(), "AssignStmt is unimplemented");
}

void IRGenFunction::emitIfStmt(IfStmt *S) {
  unimplemented(S->getLocStart(), "IfStmt is unimplemented");
}

void IRGenFunction::emitReturnStmt(ReturnStmt *S) {
  unimplemented(S->getLocStart(), "ReturnStmt is unimplemented");
}

void IRGenFunction::emitWhileStmt(WhileStmt *S) {
  unimplemented(S->getLocStart(), "WhileStmt is unimplemented");
}
