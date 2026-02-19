import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import LoginPage from "./components/loginPage.jsx";
import logo from "./assets/instagram_logo.png";
import "./App.css";

// This is the Home screen component
function Home() {
  const handleLoginClick = () => {
    // window.open(url, target) is the standard web API to open a new tab
    // We point it to the '/login' route we'll define in the Router below
    window.open("/login", "_blank");
  };

  return (
    <div className="home-container">
      <img src={logo} alt="Company Logo" className="app-logo" />
      <h1>Ericstagram</h1>
      <button className="log-in-button" onClick={handleLoginClick}>
        Log in
      </button>
    </div>
  );
}

function App() {
  return (
    <Router>
      <Routes>
        {/* The main page of your app */}
        <Route path="/" element={<Home />} />

        {/* The login page that will be shown in the new tab */}
        <Route
          path="/login"
          element={
            <LoginPage
              onLogin={(user) => console.log("Successfully logged in:", user)}
            />
          }
        />
      </Routes>
    </Router>
  );
}

export default App;
