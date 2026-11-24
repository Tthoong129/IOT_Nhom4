// Node-RED runtime settings for IoT Smart Parking (Nhom 4)
// Mat khau duoc luu duoi dang bcrypt hash ($2b$08$...), khong luu mat khau tho trong ma nguon.
// Co the ghi de bang bien moi truong NODERED_UI_USER / NODERED_UI_PASS_HASH trong Docker.

const uiUser = process.env.NODERED_UI_USER || "admin";
const uiPassHash = process.env.NODERED_UI_PASS_HASH || "$2b$08$4wiR9/4FssxJyJCeUJSWQ.4LHrBYhzIAwRJbnk24duDldGGPJ0vVC";
const adminUser = process.env.NODERED_ADMIN_USER || "admin";
const adminPassHash = process.env.NODERED_ADMIN_PASS_HASH || "$2b$08$4wiR9/4FssxJyJCeUJSWQ.4LHrBYhzIAwRJbnk24duDldGGPJ0vVC";

module.exports = {
    flowFile: "flows.json",
    flowFilePretty: true,
    uiPort: process.env.PORT || 1880,

    // Xac thuc Flow Editor (/)
    adminAuth: {
        type: "credentials",
        users: [{
            username: adminUser,
            password: adminPassHash,
            permissions: "*"
        }]
    },

    // Xac thuc Web Dashboard (/ui) bang HTTP Basic Auth
    httpNodeAuth: {
        user: uiUser,
        pass: uiPassHash
    },

    diagnostics: {
        enabled: true,
        ui: true
    },

    runtimeState: {
        enabled: false,
        ui: false
    },

    logging: {
        console: {
            level: "info",
            metrics: false,
            audit: false
        }
    },

    editorTheme: {
        projects: {
            enabled: false
        }
    },

    functionExternalModules: false,
    functionGlobalContext: {}
};
