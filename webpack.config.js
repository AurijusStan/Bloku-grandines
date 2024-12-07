const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  mode: "development", // Set to 'development' for local testing
  entry: "./front-end/src/app.js", // Entry point for your app
  output: {
    path: path.resolve(__dirname, "dist"),
    filename: "bundle.js", // Output JavaScript file
    clean: true, // Clean the output directory before each build
  },
  devServer: {
    static: "./dist", // Serve files from the 'dist' folder
    port: 8080, // Default port for the dev server
    open: true, // Automatically open the browser
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "./front-end/public/index.html", // Use your custom HTML file
    }),
  ],
  module: {
    rules: [
      {
        test: /\.css$/i,
        use: ["style-loader", "css-loader"], // Load CSS files
      },
    ],
  },
};
