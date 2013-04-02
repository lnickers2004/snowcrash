//
//  MarkdownParser.h
//  snowcrash
//
//  Created by Zdenek Nemec on 4/15/13.
//  Copyright (c) 2013 Apiary.io. All rights reserved.
//

#ifndef SNOWCRASH_MARKDOWNPARSER_H
#define SNOWCRASH_MARKDOWNPARSER_H

#include "Parser.h"
#include "MarkdownBlock.h"
#include "markdown.h"

namespace snowcrash {
    
    //
    // Markdown Parser
    //
    class MarkdownParser {
    public:
        // Default sundown parser configuration
        const size_t OutputUnitSize = 64;
        const size_t MaxNesting = 16;
        const int ParserExtensions = MKDEXT_FENCED_CODE | MKDEXT_NO_INTRA_EMPHASIS /*| MKDEXT_TABLES */;
        
        using ParseHandler = std::function<void(const Result&, const MarkdownBlock&)>;
        
        // Parse source Markdown into Markdown AST
        void parse(const SourceData& source, const ParseHandler& callback);
    
    private:
        using RenderCallbacks = sd_callbacks;
        using RenderCallbackData = void *;
    
        RenderCallbacks renderCallbacks();
        RenderCallbackData renderCallbackData();
        
        using RenderStack = std::vector<MarkdownBlock::Stack>;
        RenderStack m_renderContext;
        
        void pushRenderContext();
        void popRenderContext();
        
        // Header
        static void renderHeader(struct buf *ob, const struct buf *text, int level, void *opaque);
        void renderHeader(const std::string& text, int level);
        
        // List
        static void beginList(int flags, void *opaque);
        void beginList(int flags);
        
        static void renderList(struct buf *ob, const struct buf *text, int flags, void *opaque);
        void renderList(const std::string& text, int flags);
        
        // List item
        static void beginListItem(int flags, void *opaque);
        void beginListItem(int flags);
        
        static void renderListItem(struct buf *ob, const struct buf *text, int flags, void *opaque);
        void renderListItem(const std::string& text, int flags);
        
        // Code block
        static void renderBlockCode(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque);
        void renderBlockCode(const std::string& text, const std::string& language);
        
        // Paragraph
        static void renderParagraph(struct buf *ob, const struct buf *text, void *opaque);
        void renderParagraph(const std::string& text);
        
        // Horizontal Rule
        static void renderHorizontalRule(struct buf *ob, void *opaque);
        void renderHorizontalRule();

        // HTML
        static void renderHTML(struct buf *ob, const struct buf *text, void *opaque);
        void renderHTML(const std::string& text);
    
        // Quote
        static void beginQuote(void *opaque);
        void beginQuote();
    
        static void renderQuote(struct buf *ob, const struct buf *text, void *opaque);
        void renderQuote(const std::string& text);
        
        // Source maps
        static void blockDidParse(const src_map* map, const uint8_t *txt_data, size_t size, void *opaque);
        void blockDidParse(const SourceDataBlock& sourceMap);
    };
}

#endif
