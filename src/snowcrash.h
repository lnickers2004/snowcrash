//
//  snowcrash.h
//  snowcrash
//
//  Created by Zdenek Nemec on 4/2/13.
//  Copyright (c) 2013 Apiary.io. All rights reserved.
//

#ifndef SNOWCRASH_H
#define SNOWCRASH_H

#include "Blueprint.h"
#include "Parser.h"

namespace snowcrash {
    
    // Convenience wrapper for Parser's parse method
    void parse(const SourceData& source, const Parser::ParseHandler& callback);
}

#endif
