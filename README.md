{"payload":{"allShortcutsEnabled":true,"fileTree":{"":{"items":[{"name":"include","path":"include","contentType":"directory"},{"name":"lib","path":"lib","contentType":"directory"},{"name":"src","path":"src","contentType":"directory"},{"name":"test","path":"test","contentType":"directory"},{"name":".gitignore","path":".gitignore","contentType":"file"},{"name":".travis.yml","path":".travis.yml","contentType":"file"},{"name":"LICENSE","path":"LICENSE","contentType":"file"},{"name":"README.md","path":"README.md","contentType":"file"},{"name":"platformio.ini","path":"platformio.ini","contentType":"file"}],"totalCount":9}},"fileTreeProcessingTime":1.931759,"foldersToFetch":[],"reducedMotionEnabled":"system","repo":{"id":165415249,"defaultBranch":"master","name":"higrow-mqtt-sender","ownerLogin":"tom-mi","currentUserCanPush":false,"isFork":false,"isEmpty":false,"createdAt":"2019-01-13T04:23:10.000+11:00","ownerAvatar":"https://avatars.githubusercontent.com/u/3297149?v=4","public":true,"private":false,"isOrgOwned":false},"symbolsExpanded":true,"treeExpanded":true,"refInfo":{"name":"master","listCacheKey":"v0:1547340323.0","canEdit":true,"refType":"branch","currentOid":"783013fe402149db5cc2fb1ea12deaba2c1fc657"},"path":"README.md","currentUser":{"id":3615980,"login":"phildimond","userEmail":"phil@adgaming.com.au"},"blob":{"rawLines":null,"stylingDirectives":null,"csv":null,"csvError":null,"dependabotInfo":{"showConfigurationBanner":false,"configFilePath":null,"networkDependabotPath":"/tom-mi/higrow-mqtt-sender/network/updates","dismissConfigurationNoticePath":"/settings/dismiss-notice/dependabot_configuration_notice","configurationNoticeDismissed":false,"repoAlertsPath":"/tom-mi/higrow-mqtt-sender/security/dependabot","repoSecurityAndAnalysisPath":"/tom-mi/higrow-mqtt-sender/settings/security_analysis","repoOwnerIsOrg":false,"currentUserCanAdminRepo":false},"displayName":"README.md","displayUrl":"https://github.com/tom-mi/higrow-mqtt-sender/blob/master/README.md?raw=true","headerInfo":{"blobSize":"952 Bytes","deleteInfo":{"deleteTooltip":"Fork this repository and delete the file"},"editInfo":{"editTooltip":"Fork this repository and edit the file"},"ghDesktopPath":"x-github-client://openRepo/https://github.com/tom-mi/higrow-mqtt-sender?branch=master&filepath=README.md","gitLfsPath":null,"onBranch":true,"shortPath":"0279141","siteNavLoginPath":"/login?return_to=https%3A%2F%2Fgithub.com%2Ftom-mi%2Fhigrow-mqtt-sender%2Fblob%2Fmaster%2FREADME.md","isCSV":false,"isRichtext":true,"toc":[{"level":1,"text":"higrow-mqtt-sender","anchor":"higrow-mqtt-sender","htmlText":"higrow-mqtt-sender"},{"level":2,"text":"Overview","anchor":"overview","htmlText":"Overview"},{"level":2,"text":"Deployment","anchor":"deployment","htmlText":"Deployment"}],"lineInfo":{"truncatedLoc":"26","truncatedSloc":"18"},"mode":"file"},"image":false,"isCodeownersFile":null,"isPlain":false,"isValidLegacyIssueTemplate":false,"issueTemplateHelpUrl":"https://docs.github.com/articles/about-issue-and-pull-request-templates","issueTemplate":null,"discussionTemplate":null,"language":"Markdown","languageID":222,"large":false,"loggedIn":true,"newDiscussionPath":"/tom-mi/higrow-mqtt-sender/discussions/new","newIssuePath":"/tom-mi/higrow-mqtt-sender/issues/new","planSupportInfo":{"repoIsFork":null,"repoOwnedByCurrentUser":null,"requestFullPath":"/tom-mi/higrow-mqtt-sender/blob/master/README.md","showFreeOrgGatedFeatureMessage":null,"showPlanSupportBanner":null,"upgradeDataAttributes":null,"upgradePath":null},"publishBannersInfo":{"dismissActionNoticePath":"/settings/dismiss-notice/publish_action_from_dockerfile","dismissStackNoticePath":"/settings/dismiss-notice/publish_stack_from_file","releasePath":"/tom-mi/higrow-mqtt-sender/releases/new?marketplace=true","showPublishActionBanner":false,"showPublishStackBanner":false},"renderImageOrRaw":false,"richText":"<article class=\"markdown-body entry-content container-lg\" itemprop=\"text\"><h1 tabindex=\"-1\" id=\"user-content-higrow-mqtt-sender\" dir=\"auto\"><a class=\"heading-link\" href=\"#higrow-mqtt-sender\">higrow-mqtt-sender<svg class=\"octicon octicon-link\" viewBox=\"0 0 16 16\" version=\"1.1\" width=\"16\" height=\"16\" aria-hidden=\"true\"><path d=\"m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z\"></path></svg></a></h1>\n<p dir=\"auto\">Firmware for the <a href=\"https://hackaday.io/project/25253-higrow-plants-monitoring-sensor\" rel=\"nofollow\">HiGrow Plants Monitoring Sensor</a>\nthat sends sensor readings to a MQTT broker</p>\n<h2 tabindex=\"-1\" id=\"user-content-overview\" dir=\"auto\"><a class=\"heading-link\" href=\"#overview\">Overview<svg class=\"octicon octicon-link\" viewBox=\"0 0 16 16\" version=\"1.1\" width=\"16\" height=\"16\" aria-hidden=\"true\"><path d=\"m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z\"></path></svg></a></h2>\n<p dir=\"auto\">The firmware will send the following values to a MQTT topic named <code>higrow_plant_monitor/$device_id/state</code>:</p>\n<ul dir=\"auto\">\n<li><code>device_id</code> - equals the MAC address of the builtin ESP32)</li>\n<li><code>temperature_celsius</code> - Air temperature recorded by the DHT11 sensor</li>\n<li><code>humidity_percent</code> - Air humidity recorded by the DHT11 sensor</li>\n<li><code>water</code> - Soil water level (0..1, calibrated with air / a glass of water)</li>\n<li><code>light</code> - Taken from the official firmware, but seems not to work with older versions of the board. Not calibrated.</li>\n</ul>\n<h2 tabindex=\"-1\" id=\"user-content-deployment\" dir=\"auto\"><a class=\"heading-link\" href=\"#deployment\">Deployment<svg class=\"octicon octicon-link\" viewBox=\"0 0 16 16\" version=\"1.1\" width=\"16\" height=\"16\" aria-hidden=\"true\"><path d=\"m7.775 3.275 1.25-1.25a3.5 3.5 0 1 1 4.95 4.95l-2.5 2.5a3.5 3.5 0 0 1-4.95 0 .751.751 0 0 1 .018-1.042.751.751 0 0 1 1.042-.018 1.998 1.998 0 0 0 2.83 0l2.5-2.5a2.002 2.002 0 0 0-2.83-2.83l-1.25 1.25a.751.751 0 0 1-1.042-.018.751.751 0 0 1-.018-1.042Zm-4.69 9.64a1.998 1.998 0 0 0 2.83 0l1.25-1.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042l-1.25 1.25a3.5 3.5 0 1 1-4.95-4.95l2.5-2.5a3.5 3.5 0 0 1 4.95 0 .751.751 0 0 1-.018 1.042.751.751 0 0 1-1.042.018 1.998 1.998 0 0 0-2.83 0l-2.5 2.5a1.998 1.998 0 0 0 0 2.83Z\"></path></svg></a></h2>\n<p dir=\"auto\">Declare the following environment variables according to your environment:</p>\n<div class=\"snippet-clipboard-content notranslate position-relative overflow-auto\" data-snippet-clipboard-copy-content=\"WIFI_SSID\nWIFI_PASS\nMQTT_BROKER_HOST\nMQTT_BROKER_PORT\"><pre class=\"notranslate\"><code>WIFI_SSID\nWIFI_PASS\nMQTT_BROKER_HOST\nMQTT_BROKER_PORT\n</code></pre></div>\n<p dir=\"auto\">Connect the device via USB and flash it with platformio:</p>\n<div class=\"snippet-clipboard-content notranslate position-relative overflow-auto\" data-snippet-clipboard-copy-content=\"platformio run --target upload\"><pre class=\"notranslate\"><code>platformio run --target upload\n</code></pre></div>\n</article>","renderedFileInfo":null,"shortPath":null,"tabSize":8,"topBannersInfo":{"overridingGlobalFundingFile":false,"globalPreferredFundingPath":null,"repoOwner":"tom-mi","repoName":"higrow-mqtt-sender","showInvalidCitationWarning":false,"citationHelpUrl":"https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/creating-a-repository-on-github/about-citation-files","showDependabotConfigurationBanner":false,"actionsOnboardingTip":null},"truncated":false,"viewable":true,"workflowRedirectUrl":null,"symbols":{"timedOut":false,"notAnalyzed":false,"symbols":[{"name":" higrow-mqtt-sender","kind":"section_1","identStart":1,"identEnd":20,"extentStart":0,"extentEnd":952,"fullyQualifiedName":" higrow-mqtt-sender","identUtf16":{"start":{"lineNumber":0,"utf16Col":1},"end":{"lineNumber":0,"utf16Col":20}},"extentUtf16":{"start":{"lineNumber":0,"utf16Col":0},"end":{"lineNumber":26,"utf16Col":0}}},{"name":" Overview","kind":"section_2","identStart":187,"identEnd":196,"extentStart":185,"extentEnd":697,"fullyQualifiedName":" Overview","identUtf16":{"start":{"lineNumber":5,"utf16Col":2},"end":{"lineNumber":5,"utf16Col":11}},"extentUtf16":{"start":{"lineNumber":5,"utf16Col":0},"end":{"lineNumber":14,"utf16Col":0}}},{"name":" Deployment","kind":"section_2","identStart":699,"identEnd":710,"extentStart":697,"extentEnd":952,"fullyQualifiedName":" Deployment","identUtf16":{"start":{"lineNumber":14,"utf16Col":2},"end":{"lineNumber":14,"utf16Col":13}},"extentUtf16":{"start":{"lineNumber":14,"utf16Col":0},"end":{"lineNumber":26,"utf16Col":0}}}]}},"copilotInfo":{"documentationUrl":"https://docs.github.com/copilot/overview-of-github-copilot/about-github-copilot-for-business","notices":{"codeViewPopover":{"dismissed":false,"dismissPath":"/settings/dismiss-notice/code_view_copilot_popover"}},"userAccess":{"accessAllowed":false,"hasSubscriptionEnded":false,"orgHasCFBAccess":false,"userHasCFIAccess":false,"userHasOrgs":true,"userIsOrgAdmin":false,"userIsOrgMember":false,"business":null,"featureRequestInfo":null}},"csrf_tokens":{"/tom-mi/higrow-mqtt-sender/branches":{"post":"oo6tlmz40zYrgUt2KuUG5S_Rw0b7eB4zOQhag7HKHcTvOBE4L2uKCikCYFXLFJ2RMvE_7bkmYZszDWt9k9mpew"},"/repos/preferences":{"post":"vejiiJCuHLfUaNoInTtb4JyTyLFScyDerLEbPrP1tHuNK52nGgbSYCh0l1D0Yx5Z41u-mi2JjOyVd6noeKfAZQ"}}},"title":"higrow-mqtt-sender/README.md at master · tom-mi/higrow-mqtt-sender"}