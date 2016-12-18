# Drupal Module: Region Tokens
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

##Summary
**The aim of this module is to provide Content Managers with a means to place a region (one or more blocks) anywhere within the content of a node.**

This is achieved by using tokens that represent block regions, which are inserted into the node content.  These tokens are rendered into their respective regions and the blocks assigned to the regions thus appear inside the node content.

Since we're using a token, the placement of the region can and will vary from node to node.  This can be thought of as an "inline" region.

The block visibility settings (Pages, Content Types, Roles, Users) work just as you would expect under the normal circumstances of a standard region.

This module is one answer to the question, "How do I place blocks inside of nodes?"  It takes a slightly different approace than the Insert Block module (read more below).

You may also visit the [project page](http://www.drupal.org/project/region_tokens) on Drupal.org.

##Requirements
You must have the [Token](https://drupal.org/project/token) module enabled.  While not technically required, for foreseen use cases you need to also install/enable [Token Filter](https://drupal.org/project/token_filter).

##Installation
1. Install as usual, see [http://drupal.org/node/70151](http://drupal.org/node/70151) for further information.
2. Unless you deem unneccessary, make sure you have [Token Filter](https://drupal.org/project/token_filter) installed and enabled.

##Configuration
1. Visit `/admin/config/content/region-tokens` and define one or more regions to be available as tokens.  These will now be visible in the token tree under the group _Regions_.
2. Now make sure you have at least one block assigned to the region you just enabled.
3. Inside the node edit form wherein you wish to place the region, insert the appropriate region token. (For a list of tokens visit: `/admin/help/token` and refer to the token group _Regions_.)
4. After saving the node, you should see the region rendered in place of the token, inside the node content!
5. If you do not see what you expected, take a look at the Recent log messages `/admin/reports/dblog`.

##Suggested Use
1. In practice, we create one or more extra regions in my theme devoted only to this type of thing, something like:

        regions[inline] = Inline
        regions[inline2] = Inline 2        
        
2. Be aware that if you set your visibility settings incorrectly, the block token will return an empty string, rather than the region you're expecting.

3. In the fringe case where you find a need to place two blocks on the same page, in separate locations, you will need to utilize two separate regions, as this is the only way to create multiple tokens, thus achieving the multiple insertion points.

## Performance Note
1. **It is critical for performance sake that you set the block visibility to ONLY those node pages** where you will be implementing the tokens.  For more information read [this post](http://www.lullabot.com/blog/article/drupal-performance-tip-block-visibility) by Angie Byron.

## Design Decisions/Rationale
Having blocks that are being used via insert of a token, but which appear as disabled on the Block admin page was confusing to our Content Manager(s).  This sometimes led to blocks getting deleted, which should not have been deleted, only to find that out later.  We were looking for an approach that was more intuitive in terms of the core Block system.

##Similar Module(s)

### [Insert Block](https://drupal.org/project/insert_block)
*Region Tokens* differs in that it thinks in terms of a region, rather than a single block.  Also, mechanically speaking, Insert Block is a filter, whereas this module works by providing a token and then leveraging the [Token Filter](https://drupal.org/project/token_filter) module to do the inserting of said token into the content.

### Reason(s) to Use *Insert Block*
1. **Block re-use across multiple regions.** If you need to insert a block that is already being used in another region, you would need to choose the Insert Block module over this one.
2. **No access to the theme.**  If you will not be modifying your theme files, you may want to go with the Insert Block module.

### Reason(s) to Use *Region Tokens*
1. **Clearer UI for admins.**  By using a dedicated "inline" region (as described in Suggested Use), the blocks overview screen will accurately reflect which blocks are disabled and which are in use.  Unless a block is assigned to a region it appears like it's disabled in the UI.  When using the Insert Block module a "disabled block" can be effectively "enabled" just by inserting it in a content field.  However, in such a case, the UI is not accurately reflecting reality.  **Using this module you will not accidentally delete a supposedly "disabled" block.**
2. **Fewer tokens to remember.**  Since there is one token per region your Content Manager(s) will generally only need to remember one or two tokens, rather than having to compose the block insert token based on `module_name` and `delta`.

##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>
