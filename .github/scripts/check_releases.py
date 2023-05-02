#!/usr/bin/env python3

import argparse
import hashlib
import requests
import tempfile
import re
import shutil
import sys
import os

# Get all versions of package from pypi
# python script/get_releases.py flux-framework

token = os.environ.get("GITHUB_TOKEN")
headers = {}
if token:
    headers["Authorization"] = "token %s" % token


def set_env_and_output(name, value):
    """
    helper function to echo a key/value pair to output and env.

    Parameters:
    name (str)  : the name of the environment variable
    value (str) : the value to write to file
    """
    for env_var in ("GITHUB_ENV", "GITHUB_OUTPUT"):
        environment_file_path = os.environ.get(env_var)
        print("Writing %s=%s to %s" % (name, value, env_var))

        with open(environment_file_path, "a") as environment_file:
            environment_file.write("%s=%s\n" % (name, value))


class PackageUpdater:
    def __init__(
        self, package, version=None, dry_run=False, repo="flux-framework/flux-core"
    ):
        self.package = package
        self.dry_run = dry_run
        self.version = version
        self.repo = repo

    def check(self):
        """
        Given a package directory and repository name, check for new releases.
        """
        releases = self.get_github_releases()

        # The latest tag
        tag = releases[0]["tag_name"]
        if self.version is not None:
            tag = self.version

        # Get releases from pypi
        pypi_releases = self.get_pypi_releases()

        # Some versions are prefixed with v
        tags = [tag, tag.lstrip("v")]

        # If it's a dry run OR we don't have it
        if self.dry_run or (
            tags[0] not in pypi_releases and tags[1] not in pypi_releases
        ):
            print(f"New version {tag} detected or dry run is set!")
            set_env_and_output("version", tag)
            set_env_and_output("build", "true")
            set_env_and_output("dry-run", self.dry_run)
        else:
            print(f"Tag {tag} is already released and dry run is false")

    def get_pypi_releases(self):
        """
        Get releases to pypi
        """
        res = requests.get(f"https://pypi.org/pypi/{self.package}/json")
        if res.status_code == 404:
            return []
        if res.status_code != 200:
            sys.exit(f"Issue getting pypi releases: {res.txt}")
        res = res.json()

        # earliest (index 0) to latest (index -1)
        return list(res["releases"])

    def get_github_releases(self):
        """
        Get the lateset release of a repository (under flux-framework)
        """
        url = f"https://api.github.com/repos/{self.repo}/releases"
        response = requests.get(url, headers=headers, params={"per_page": 100})
        response.raise_for_status()

        # latest release should be first
        return response.json()

    def download_archive(self, naked_version, download_path):
        """
        Download an archive tarball.
        """
        tarball_url = (
            f"https://github.com/{self.repo}/archive/refs/tags/{naked_version}.tar.gz"
        )
        return self.download(tarball_url, download_path)


def get_parser():
    parser = argparse.ArgumentParser(
        description="Spack Updater for Releases",
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument("package", help="name of pypi package")
    parser.add_argument("--version", help="version of flux to target")
    parser.add_argument(
        "--repo", default="flux-framework/flux-core", help="repository with releases"
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        default=False,
        help="Don't write changes to file",
    )
    return parser


def main():
    parser = get_parser()

    # If an error occurs while parsing the arguments, the interpreter will exit with value 2
    args, extra = parser.parse_known_args()

    # Show args to the user
    print("        repo: %s" % args.repo)
    print("     package: %s" % args.package)
    print("     dry-run: %s" % args.dry_run)
    if args.version:
        print("     version: %s" % args.version)

    updater = PackageUpdater(args.package, args.version, args.dry_run)
    updater.check()


if __name__ == "__main__":
    main()
