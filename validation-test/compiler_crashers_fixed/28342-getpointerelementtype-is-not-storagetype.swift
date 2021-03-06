// This source file is part of the Swift.org open source project
// Copyright (c) 2014 - 2016 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors

// RUN: %target-swift-frontend %s -emit-ir
protocol A {
    associatedtype B
}
struct C<T: A> {
    let d: T
}
protocol E {
    associatedtype F
    func g<T where F == T.B>(_: C<T>)
}
struct H: E {
    typealias F = Void
    func g<T where F == T.B>(_: C<T>) {}
}
